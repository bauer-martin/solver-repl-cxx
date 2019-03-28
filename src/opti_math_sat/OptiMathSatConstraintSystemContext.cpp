#include "OptiMathSatConstraintSystemContext.h"

#include <boost/algorithm/string.hpp>
#include <string>
#include <stdexcept>

#include "utilities/Helpers.h"

namespace opti_math_sat {

OptiMathSatConstraintSystemContext::OptiMathSatConstraintSystemContext(
    const spl_conqueror::VariabilityModel &vm,
    msat_config &config,
    msat_env &environment,
    std::vector<msat_term> variables,
    msat_term &feature_model)
    : _vm(vm),
      _config(config),
      _environment(environment),
      _variables(std::move(variables)),
      _option_name_to_variable_index(),
      _feature_model(feature_model) {
  create_variables();
  process_binary_options();
  process_binary_constraints();
  msat_assert_formula(_environment, _feature_model);
}

OptiMathSatConstraintSystemContext *OptiMathSatConstraintSystemContext::make_from(
    const spl_conqueror::VariabilityModel &vm) {
  msat_config config = msat_create_config();
  msat_set_option(config, "model_generation", "true");
  msat_set_option(config, "random_seed", "42");
  msat_env environment = msat_create_opt_env(config);
  std::vector<msat_term> variables(vm.get_binary_options().size());
  msat_term feature_model = msat_make_true(environment);
  return new OptiMathSatConstraintSystemContext(vm, config, environment, variables, feature_model);
}

OptiMathSatConstraintSystemContext::~OptiMathSatConstraintSystemContext() {
  msat_destroy_env(_environment);
  msat_destroy_config(_config);
}

const msat_term &OptiMathSatConstraintSystemContext::option_to_var(const spl_conqueror::BinaryOption &option) const {
  const std::string &name = option.get_name();
  int index = _option_name_to_variable_index.at(name);
  return _variables.at(index);
}

const msat_env &OptiMathSatConstraintSystemContext::get_environment() const {
  return _environment;
}

const spl_conqueror::VariabilityModel &OptiMathSatConstraintSystemContext::get_variability_model() const {
  return _vm;
}

void OptiMathSatConstraintSystemContext::add_constraint(const msat_term &term) {
  _feature_model = msat_make_and(_environment, _feature_model, term);
}

msat_term assign(const msat_env &env, const msat_term &term, bool value) {
  return msat_make_equal(env, term, msat_make_number(env, value ? "1" : "0"));
}

void OptiMathSatConstraintSystemContext::create_variables() {
  const std::vector<spl_conqueror::BinaryOption *> &options = _vm.get_binary_options();
  msat_type int_type = msat_get_integer_type(_environment);
  for (int i = 0; i < options.size(); ++i) {
    spl_conqueror::BinaryOption *option = options[i];
    msat_decl variable_decl = msat_declare_function(_environment, option->get_name().c_str(), int_type);
    const msat_term &variable = msat_make_constant(_environment, variable_decl);
    _variables[i] = variable;
    _option_name_to_variable_index[option->get_name()] = i;
    // 0 <= variable <= 1
    add_constraint(msat_make_leq(_environment, msat_make_number(_environment, "0"), variable));
    add_constraint(msat_make_leq(_environment, variable, msat_make_number(_environment, "1")));
  }
}

void OptiMathSatConstraintSystemContext::process_binary_options() {
  std::set<std::string> processed_alternatives;
  for (auto &&option : _vm.get_binary_options()) {
    add_variable_constraints(*option);
    process_alternative_options(processed_alternatives, *option);
    process_excluded_options_as_cross_tree_constraints(*option);
    process_implied_options(*option);
  }
}

void OptiMathSatConstraintSystemContext::add_variable_constraints(const spl_conqueror::BinaryOption &option) {
  const msat_term &variable = option_to_var(option);
  if (option.is_root()) {
    add_constraint(assign(_environment, variable, true));
  } else if (option.has_parent()) {
    const msat_term &parent_var = option_to_var(*option.get_parent());
    if (option.is_mandatory() && !option.has_excluded_options()) {
      // variable <=> parent_var
      add_constraint(msat_make_equal(_environment, variable, parent_var));
    } else {
      // variable => parent_var
      add_constraint(msat_make_or(_environment,
                                  assign(_environment, variable, false),
                                  assign(_environment, parent_var, true)));
    }
  } else {
    throw std::runtime_error(option.get_name() + " has no parent");
  }
}

void OptiMathSatConstraintSystemContext::process_alternative_options(
    std::set<std::string> &processed_alternatives,
    const spl_conqueror::BinaryOption &option) {
  const std::vector<spl_conqueror::BinaryOption *> &options = option.collect_alternative_options();
  if (options.empty() || processed_alternatives.find(option.get_name()) != processed_alternatives.end()) {
    return;
  }
  msat_term sum_term = option_to_var(option);
  processed_alternatives.insert(option.get_name());
  for (auto &&alternative : options) {
    sum_term = msat_make_plus(_environment,
                              sum_term,
                              option_to_var(*alternative));
    processed_alternatives.insert(alternative->get_name());
  }
  const msat_term &parent_var = option_to_var(*option.get_parent());
  // parent_var => sum of alternative options = 1
  add_constraint(msat_make_or(_environment,
                              assign(_environment, parent_var, false),
                              msat_make_equal(_environment,
                                              sum_term,
                                              msat_make_number(_environment, "1"))));
}

void OptiMathSatConstraintSystemContext::process_excluded_options_as_cross_tree_constraints(
    const spl_conqueror::BinaryOption &option) {
  for (auto &&non_alternative_options : option.get_non_alternative_excluded_options()) {
    msat_term or_term = msat_make_false(_environment);
    for (auto &&o : non_alternative_options) {
      or_term = msat_make_or(_environment, or_term, assign(_environment, option_to_var(*o), true));
    }
    // option => not ( or of non alternative excluded options )
    add_constraint(msat_make_or(_environment,
                                assign(_environment, option_to_var(option), false),
                                msat_make_not(_environment, or_term)));
  }
}

void OptiMathSatConstraintSystemContext::process_implied_options(const spl_conqueror::BinaryOption &option) {
  for (auto &&implied_options : option.get_implied_options()) {
    msat_term or_term = msat_make_false(_environment);
    for (auto &&o : implied_options) {
      or_term = msat_make_or(_environment, or_term, assign(_environment, option_to_var(*o), true));
    }
    // option => or of implied options
    add_constraint(msat_make_or(_environment,
                                assign(_environment, option_to_var(option), false),
                                or_term));
  }
}

void OptiMathSatConstraintSystemContext::process_binary_constraints() {
  for (auto &&constraint_string : _vm.get_binary_constraints()) {
    std::vector<std::string> terms;
    if (constraint_string.find('&') != std::string::npos) {
      boost::split(terms, constraint_string, boost::is_any_of("&"));
      msat_term and_term = msat_make_true(_environment);
      for (auto &&option_name : terms) {
        helpers::trim(option_name);
        if (option_name.at(0) == '!') {
          option_name = option_name.substr(1);
          spl_conqueror::BinaryOption *option = _vm.get_binary_option(option_name);
          and_term = msat_make_and(_environment, and_term, assign(_environment, option_to_var(*option), false));
        } else {
          spl_conqueror::BinaryOption *option = _vm.get_binary_option(option_name);
          and_term = msat_make_and(_environment, and_term, assign(_environment, option_to_var(*option), true));
        }
      }
      add_constraint(and_term);
    } else {
      boost::split(terms, constraint_string, boost::is_any_of("|"));
      msat_term or_term = msat_make_false(_environment);
      for (auto &&option_name : terms) {
        helpers::trim(option_name);
        if (option_name.at(0) == '!') {
          option_name = option_name.substr(1);
          spl_conqueror::BinaryOption *option = _vm.get_binary_option(option_name);
          or_term = msat_make_or(_environment, or_term, assign(_environment, option_to_var(*option), false));
        } else {
          spl_conqueror::BinaryOption *option = _vm.get_binary_option(option_name);
          or_term = msat_make_or(_environment, or_term, assign(_environment, option_to_var(*option), true));
        }
      }
      add_constraint(or_term);
    }
  }
}

void OptiMathSatConstraintSystemContext::mark_checkpoint() {
  msat_gc_env(_environment, nullptr, 0);
  msat_push_backtrack_point(_environment);
}

void OptiMathSatConstraintSystemContext::reset_to_last_checkpoint() {
  msat_pop_backtrack_point(_environment);
}

}
