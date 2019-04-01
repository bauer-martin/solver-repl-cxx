#include "OrToolsSatChecker.h"

#include "OrToolsConstraintSystemContext.h"
#include "OrToolsHelper.h"
#include "utilities/Helpers.h"

namespace or_tools {

OrToolsSatChecker::OrToolsSatChecker(const spl_conqueror::VariabilityModel &vm) : _vm(vm) {
}

static void select_features_and_deselect_all_others(
    OrToolsConstraintSystemContext &context,
    const std::vector<spl_conqueror::BinaryOption *> &selected_options) {
  std::vector<ort::BoolVar> and_vars;
  std::vector<spl_conqueror::BinaryOption *> options = context.get_variability_model().get_binary_options();
  and_vars.reserve(options.size());
  for (auto &&option : options) {
    const ort::BoolVar &variable = context.option_to_var(*option);
    if (helpers::contains(selected_options, *option)) {
      and_vars.push_back(variable);
    } else {
      and_vars.push_back(variable.Not());
    }
  }
  context.get_model().AddBoolAnd(and_vars);
}

bool OrToolsSatChecker::is_valid(const std::vector<spl_conqueror::BinaryOption *> &selected_options,
                                 bool is_partial_configuration) {
  OrToolsConstraintSystemContext *context = OrToolsConstraintSystemContext::make_from(_vm);

  if (is_partial_configuration) {
    select_features(*context, selected_options);
  } else {
    select_features_and_deselect_all_others(*context, selected_options);
  }
  const ort::CpSolverStatus status = ort::Solve(context->get_model()).status();
  if (status != operations_research::sat::FEASIBLE && status != operations_research::sat::INFEASIBLE) {
    throw std::runtime_error("unknown status: " + std::to_string(status));
  }

  delete context;
  return status == ort::CpSolverStatus::FEASIBLE;
}

}
