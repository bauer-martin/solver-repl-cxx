#include "OrToolsBucketSession.h"

#include <stdexcept>

#include "OrToolsConstraintSystemContext.h"
#include "OrToolsHelper.h"
#include "OrToolsSolutionCollector.h"
#include "utilities/Helpers.h"

namespace or_tools {

OrToolsBucketSession::OrToolsBucketSession(const spl_conqueror::VariabilityModel &vm) : _vm(vm) {
}

OrToolsBucketSession::~OrToolsBucketSession() = default;

std::vector<spl_conqueror::BinaryOption *> *OrToolsBucketSession::generate_config(
    int selected_options_count,
    const std::vector<std::vector<spl_conqueror::BinaryOption *>> &feature_ranking) {
  auto search = _buckets.find(selected_options_count);
  std::vector<std::vector<spl_conqueror::BinaryOption *>> *excluded_configs;
  if (search == _buckets.end()) {
    _buckets[selected_options_count] = std::vector<std::vector<spl_conqueror::BinaryOption *>>();
    excluded_configs = &_buckets[selected_options_count];
  } else {
    excluded_configs = &search->second;
  }
  std::vector<spl_conqueror::BinaryOption *> *config = generate_config(selected_options_count,
                                                                       feature_ranking,
                                                                       *excluded_configs);
  if (config) {
    excluded_configs->push_back(*config);
  }
  return config;
}

static void setup(OrToolsConstraintSystemContext &context,
                  int selected_options_count,
                  const std::vector<std::vector<spl_conqueror::BinaryOption *>> &excluded_configs) {
  operations_research::sat::CpModelBuilder &model = context.get_model();

  // there should be exactly selectedOptionsCount features selected
  std::vector<ort::BoolVar> variables;
  std::vector<spl_conqueror::BinaryOption *> all_options = context.get_variability_model().get_binary_options();
  variables.reserve(all_options.size());
  for (auto &&option : all_options) {
    variables.push_back(context.option_to_var(*option));
  }
  model.AddEquality(ort::LinearExpr::BooleanSum(variables), selected_options_count);

  // excluded configurations should not be considered as a solution
  for (auto &&excluded_config : excluded_configs) {
    std::vector<ort::BoolVar> or_vars;
    or_vars.reserve(all_options.size());
    for (auto &&option : all_options) {
      const ort::BoolVar &variable = context.option_to_var(*option);
      if (helpers::contains(excluded_config, *option)) {
        or_vars.push_back(variable.Not());
      } else {
        or_vars.push_back(variable);
      }
    }
    model.AddBoolOr(or_vars);
  }
}

std::vector<spl_conqueror::BinaryOption *> *OrToolsBucketSession::generate_config(
    int selected_options_count,
    const std::vector<std::vector<spl_conqueror::BinaryOption *>> &feature_ranking,
    const std::vector<std::vector<spl_conqueror::BinaryOption *>> &excluded_configs) {
  // if we have a feature ranking, we can use it to approximate the optimal solution
  std::vector<spl_conqueror::BinaryOption *> *approximate_optimal = get_small_weight_config(selected_options_count,
                                                                                            feature_ranking,
                                                                                            excluded_configs);
  std::vector<spl_conqueror::BinaryOption *> *result = nullptr;
  if (approximate_optimal) {
    result = approximate_optimal;
  } else {
    OrToolsConstraintSystemContext *context = OrToolsConstraintSystemContext::make_from(_vm);
    operations_research::sat::CpModelBuilder &model = context->get_model();
    setup(*context, selected_options_count, excluded_configs);

    OrToolsSolutionCollector collector(*context, 1);
    const ort::CpSolverResponse &response = ort::SolveWithModel(model, collector.get_model());
    operations_research::sat::CpSolverStatus status = response.status();
    switch (status) {
      case operations_research::sat::FEASIBLE: {
        std::vector<std::vector<spl_conqueror::BinaryOption *>> configs = collector.get_solutions();
        result = new std::vector<spl_conqueror::BinaryOption *>(configs[0]);
        break;
      }
      case operations_research::sat::INFEASIBLE:
        break;
      default:
        throw std::runtime_error("unknown status: " + std::to_string(status));
    }
    delete context;
  }
  return result;
}

std::vector<spl_conqueror::BinaryOption *> *OrToolsBucketSession::get_small_weight_config(
    int selected_options_count,
    const std::vector<std::vector<spl_conqueror::BinaryOption *>> &feature_ranking,
    const std::vector<std::vector<spl_conqueror::BinaryOption *>> &excluded_configs) {
  std::vector<spl_conqueror::BinaryOption *> *result = nullptr;
  for (auto &&config : feature_ranking) {
    OrToolsConstraintSystemContext *context = OrToolsConstraintSystemContext::make_from(_vm);
    operations_research::sat::CpModelBuilder &model = context->get_model();
    setup(*context, selected_options_count, excluded_configs);

    // force features to be selected
    select_features(*context, config);

    // check if satisfiable
    OrToolsSolutionCollector collector(*context, 1);
    const ort::CpSolverResponse &response = ort::SolveWithModel(context->get_model(), collector.get_model());
    operations_research::sat::CpSolverStatus status = response.status();
    switch (status) {
      case operations_research::sat::FEASIBLE: {
        const std::vector<std::vector<spl_conqueror::BinaryOption *>> &configs = collector.get_solutions();
        result = new std::vector<spl_conqueror::BinaryOption *>(configs[0]);
        break;
      }
      case operations_research::sat::INFEASIBLE:
        break;
      default:
        throw std::runtime_error("unknown status: " + std::to_string(status));
    }
    delete context;

    // stop if solution has been found
    if (result) {
      break;
    }
  }
  return result;
}

}
