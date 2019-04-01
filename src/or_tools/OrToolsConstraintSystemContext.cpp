#include "OrToolsConstraintSystemContext.h"

#include <boost/algorithm/string.hpp>
#include <stdexcept>
#include <string>

#include "utilities/Helpers.h"

namespace or_tools {

OrToolsConstraintSystemContext::OrToolsConstraintSystemContext(const spl_conqueror::VariabilityModel &vm,
                                                               std::vector<ort::BoolVar> variables)
    : _vm(vm),
      _model(),
      _variables(std::move(variables)) {
  create_variables();
  process_binary_options();
  process_binary_constraints();
}

OrToolsConstraintSystemContext *OrToolsConstraintSystemContext::make_from(
    const spl_conqueror::VariabilityModel &vm) {
  std::vector<ort::BoolVar> variables(vm.get_binary_options().size());
  return new OrToolsConstraintSystemContext(vm, variables);
}

OrToolsConstraintSystemContext::~OrToolsConstraintSystemContext() = default;

const ort::BoolVar &OrToolsConstraintSystemContext::option_to_var(const spl_conqueror::BinaryOption &option) const {
  const std::string &name = option.get_name();
  int index = _option_name_to_variable_index.at(name);
  return _variables.at(index);
}

ort::CpModelBuilder &OrToolsConstraintSystemContext::get_model() {
  return _model;
}

const spl_conqueror::VariabilityModel &OrToolsConstraintSystemContext::get_variability_model() const {
  return _vm;
}

void OrToolsConstraintSystemContext::create_variables() {
  const std::vector<spl_conqueror::BinaryOption *> &options = _vm.get_binary_options();
  for (int i = 0; i < options.size(); ++i) {
    spl_conqueror::BinaryOption *option = options[i];
    const ort::BoolVar &variable = _model.NewBoolVar().WithName(option->get_name());
    _variables[i] = variable;
    _option_name_to_variable_index[option->get_name()] = i;
  }
}

void OrToolsConstraintSystemContext::process_binary_options() {
  std::set<std::string> processed_alternatives;
  for (auto &&option : _vm.get_binary_options()) {
    add_variable_constraints(*option);
    process_alternative_options(processed_alternatives, *option);
    process_excluded_options_as_cross_tree_constraints(*option);
    process_implied_options(*option);
  }
}

static void assign(ort::CpModelBuilder &model, const ort::LinearExpr &variable, bool value) {
  model.AddEquality(ort::LinearExpr(variable), ort::LinearExpr(value ? 1 : 0));
}

void OrToolsConstraintSystemContext::add_variable_constraints(const spl_conqueror::BinaryOption &option) {
  const ort::BoolVar &variable = option_to_var(option);
  if (option.is_root()) {
    _model.AddBoolAnd({variable});
    assign(_model, variable, true);
  } else if (option.has_parent()) {
    const ort::BoolVar &parent_var = option_to_var(*option.get_parent());
    if (option.is_mandatory() && !option.has_excluded_options()) {
      // variable <=> parent_var
      _model.AddEquality(variable, parent_var);
    } else {
      // variable => parent_var
      _model.AddImplication(variable, parent_var);
    }
  } else {
    throw std::runtime_error(option.get_name() + " has no parent");
  }
}

void OrToolsConstraintSystemContext::process_alternative_options(
    std::set<std::string> &processed_alternatives,
    const spl_conqueror::BinaryOption &option) {
  const std::vector<spl_conqueror::BinaryOption *> &options = option.collect_alternative_options();
  if (options.empty() || processed_alternatives.find(option.get_name()) != processed_alternatives.end()) {
    return;
  }
  std::vector<ort::BoolVar> variables;
  variables.reserve(1 + options.size());
  variables.push_back(option_to_var(option));
  processed_alternatives.insert(option.get_name());
  for (auto &&alternative : options) {
    variables.push_back(option_to_var(*alternative));
    processed_alternatives.insert(alternative->get_name());
  }
  ort::LinearExpr sum = ort::LinearExpr::BooleanSum(variables);
  const ort::BoolVar &parent_var = option_to_var(*option.get_parent());
  // parent_var => sum of alternative options = 1
  _model.AddEquality(sum, 1).OnlyEnforceIf(parent_var);
}

void OrToolsConstraintSystemContext::process_excluded_options_as_cross_tree_constraints(
    const spl_conqueror::BinaryOption &option) {
  for (auto &&non_alternative_options : option.get_non_alternative_excluded_options()) {
    std::vector<ort::BoolVar> and_vars;
    and_vars.reserve(non_alternative_options.size());
    for (auto &&o : non_alternative_options) {
      and_vars.push_back(option_to_var(*o).Not());
    }
    // option => not ( or of non alternative excluded options )
    _model.AddBoolAnd(and_vars).OnlyEnforceIf(option_to_var(option));
  }
}

void OrToolsConstraintSystemContext::process_implied_options(const spl_conqueror::BinaryOption &option) {
  for (auto &&implied_options : option.get_implied_options()) {
    std::vector<ort::BoolVar> or_vars;
    or_vars.reserve(implied_options.size());
    for (auto &&o : implied_options) {
      or_vars.push_back(option_to_var((*o)));
    }
    // option => or of implied options
    _model.AddBoolOr(or_vars).OnlyEnforceIf(option_to_var(option));
  }
}

void OrToolsConstraintSystemContext::process_binary_constraints() {
  for (auto &&constraint_string : _vm.get_binary_constraints()) {
    std::vector<std::string> terms;
    if (constraint_string.find('&') != std::string::npos) {
      boost::split(terms, constraint_string, boost::is_any_of("&"));
      std::vector<ort::BoolVar> and_vars;
      for (auto &&option_name : terms) {
        helpers::trim(option_name);
        if (option_name.at(0) == '!') {
          option_name = option_name.substr(1);
          spl_conqueror::BinaryOption *option = _vm.get_binary_option(option_name);
          and_vars.push_back(option_to_var(*option).Not());
        } else {
          spl_conqueror::BinaryOption *option = _vm.get_binary_option(option_name);
          and_vars.push_back(option_to_var(*option));
        }
      }
      _model.AddBoolAnd(and_vars);
    } else {
      boost::split(terms, constraint_string, boost::is_any_of("|"));
      std::vector<ort::BoolVar> or_vars;
      for (auto &&option_name : terms) {
        helpers::trim(option_name);
        if (option_name.at(0) == '!') {
          option_name = option_name.substr(1);
          spl_conqueror::BinaryOption *option = _vm.get_binary_option(option_name);
          or_vars.push_back(option_to_var(*option).Not());
        } else {
          spl_conqueror::BinaryOption *option = _vm.get_binary_option(option_name);
          or_vars.push_back(option_to_var(*option));
        }
      }
      _model.AddBoolOr(or_vars);
    }
  }
}

}
