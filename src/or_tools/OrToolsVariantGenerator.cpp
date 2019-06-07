#include "OrToolsVariantGenerator.h"

#include "OrToolsBucketSession.h"
#include "OrToolsConstraintSystemContext.h"
#include "OrToolsHelper.h"
#include "OrToolsSolutionCollector.h"
#include "utilities/Helpers.h"

namespace or_tools {

static void add_option_weighting(OrToolsConstraintSystemContext &context,
                                 const std::function<int64(spl_conqueror::BinaryOption *)> &weighting_function,
                                 const int *optimal_cost) {
  std::vector<spl_conqueror::BinaryOption *> options = context.get_variability_model().get_binary_options();
  std::vector<ort::BoolVar> variables;
  variables.reserve(options.size());
  std::vector<int64> coefficients;
  coefficients.reserve(options.size());
  for (auto &&option : options) {
    variables.push_back(context.option_to_var(*option));
    coefficients.push_back(weighting_function(option));
  }
  if (optimal_cost) {
    context.get_model().AddEquality(ort::LinearExpr::BooleanScalProd(variables, coefficients), *optimal_cost);
  } else {
    context.get_model().Minimize(ort::LinearExpr::BooleanScalProd(variables, coefficients));
  }
}

OrToolsVariantGenerator::OrToolsVariantGenerator(const spl_conqueror::VariabilityModel &vm)
    : _vm(vm), _seed(1) {
}

void OrToolsVariantGenerator::set_seed(unsigned int seed) {
  _seed = seed;
}

std::vector<spl_conqueror::BinaryOption *> *OrToolsVariantGenerator::find_minimized_config(
    const std::vector<spl_conqueror::BinaryOption *> &config,
    const std::vector<spl_conqueror::BinaryOption *> &unwanted_options) {
  OrToolsConstraintSystemContext *context = OrToolsConstraintSystemContext::make_from(_vm);

  select_features(*context, config);
  add_option_weighting(
      *context,
      [&unwanted_options, &config](spl_conqueror::BinaryOption *option) -> int64 {
        return helpers::contains(unwanted_options, *option)
                   && !helpers::contains(config, *option) ? 100 : 1;
      },
      nullptr);

  OrToolsSolutionCollector collector(*context, 1);
  const ort::CpSolverResponse &response = ort::SolveWithModel(context->get_model(), collector.get_model());
  std::vector<spl_conqueror::BinaryOption *> *minimal_config = nullptr;
  operations_research::sat::CpSolverStatus status = response.status();
  if (status == ort::CpSolverStatus::OPTIMAL) {
    const std::vector<std::vector<spl_conqueror::BinaryOption *>> &configs = collector.get_solutions();
    minimal_config = new std::vector<spl_conqueror::BinaryOption *>(configs[0]);
  } else if (status == ort::CpSolverStatus::INFEASIBLE) {
    // no solution found -> keep nullptr for minimal_config
  } else {
    throw std::runtime_error("unknown status: " + std::to_string(status));
  }

  delete context;
  return minimal_config;
}

std::vector<std::vector<spl_conqueror::BinaryOption *>> OrToolsVariantGenerator::find_all_maximized_configs(
    const std::vector<spl_conqueror::BinaryOption *> &config,
    const std::vector<spl_conqueror::BinaryOption *> &unwanted_options) {
  OrToolsConstraintSystemContext *context = OrToolsConstraintSystemContext::make_from(_vm);

  select_features(*context, config);
  add_option_weighting(
      *context,
      [&unwanted_options, &config](spl_conqueror::BinaryOption *option) -> int64 {
        return helpers::contains(unwanted_options, *option)
                   && !helpers::contains(config, *option) ? 100 : -1;
      },
      nullptr);

  OrToolsSolutionCollector collector_1(*context, _seed, 1);
  ort::CpSolverResponse response = ort::SolveWithModel(context->get_model(), collector_1.get_model());
  std::vector<std::vector<spl_conqueror::BinaryOption *>> all_configs;
  operations_research::sat::CpSolverStatus status = response.status();
  if (status == ort::CpSolverStatus::OPTIMAL) {
    int minimal_cost = (int) response.objective_value();
    delete context;
    context = OrToolsConstraintSystemContext::make_from(_vm);
    select_features(*context, config);
    add_option_weighting(
        *context,
        [&unwanted_options, &config](spl_conqueror::BinaryOption *option) -> int64 {
          return helpers::contains(unwanted_options, *option)
                     && !helpers::contains(config, *option) ? 100 : -1;
        },
        &minimal_cost);

    OrToolsSolutionCollector collector_2(*context, _seed);
    response = ort::SolveWithModel(context->get_model(), collector_2.get_model());
    status = response.status();
    if (status == ort::CpSolverStatus::FEASIBLE) {
      all_configs = collector_2.get_solutions();
    } else {
      throw std::runtime_error("unknown status: " + std::to_string(status));
    }
  } else {
    throw std::runtime_error("unknown status: " + std::to_string(status));
  }

  delete context;
  return all_configs;
}

std::vector<std::vector<spl_conqueror::BinaryOption *>> OrToolsVariantGenerator::generate_up_to_n_configs(int n) {
  OrToolsConstraintSystemContext *context = OrToolsConstraintSystemContext::make_from(_vm);

  std::vector<std::vector<spl_conqueror::BinaryOption *>> all_configs;
  OrToolsSolutionCollector collector(*context, _seed, n);
  const ort::CpSolverResponse &response = ort::SolveWithModel(context->get_model(), collector.get_model());
  operations_research::sat::CpSolverStatus status = response.status();
  switch (status) {
    case operations_research::sat::FEASIBLE: {
      all_configs = collector.get_solutions();
      break;
    }
    case operations_research::sat::INFEASIBLE:
      break;
    default:
      throw std::runtime_error("unknown status: " + std::to_string(status));
  }

  delete context;
  return all_configs;
}

std::vector<spl_conqueror::BinaryOption *> *OrToolsVariantGenerator::generate_config_without_option(
    const std::vector<spl_conqueror::BinaryOption *> &config,
    const spl_conqueror::BinaryOption &option_to_remove,
    std::vector<spl_conqueror::BinaryOption *> &removed_options) {
  OrToolsConstraintSystemContext *context = OrToolsConstraintSystemContext::make_from(_vm);
  operations_research::sat::CpModelBuilder &model = context->get_model();

  model.AddBoolAnd({context->option_to_var(option_to_remove).Not()});
  add_option_weighting(
      *context,
      [&config](spl_conqueror::BinaryOption *option) -> int64 {
        return helpers::contains(config, *option) ? -1000 : 1000;
      },
      nullptr);

  OrToolsSolutionCollector collector(*context, 1);
  const ort::CpSolverResponse &response = ort::SolveWithModel(context->get_model(), collector.get_model());
  std::vector<spl_conqueror::BinaryOption *> *new_config = nullptr;
  operations_research::sat::CpSolverStatus status = response.status();
  switch (status) {
    case operations_research::sat::OPTIMAL: {
      const std::vector<std::vector<spl_conqueror::BinaryOption *>> &configs = collector.get_solutions();
      new_config = new std::vector<spl_conqueror::BinaryOption *>(configs[0]);
      break;
    }
    case operations_research::sat::INFEASIBLE:
      break;
    default:
      throw std::runtime_error("unknown status: " + std::to_string(status));
  }

  delete context;
  return new_config;
}

std::set<std::vector<spl_conqueror::BinaryOption *>> OrToolsVariantGenerator::generate_all_variants(
    const std::vector<spl_conqueror::BinaryOption *> &options_to_consider) {
  OrToolsConstraintSystemContext *context = OrToolsConstraintSystemContext::make_from(_vm);

  OrToolsSolutionCollector collector(*context, _seed);
  const ort::CpSolverResponse &response = ort::SolveWithModel(context->get_model(), collector.get_model());
  std::set<std::vector<spl_conqueror::BinaryOption *>> all_configs;
  operations_research::sat::CpSolverStatus status = response.status();
  switch (status) {
    case operations_research::sat::FEASIBLE: {
      const std::vector<std::vector<spl_conqueror::BinaryOption *>> &solutions = collector.get_solutions();
      for (auto &&full_config : solutions) {
        std::vector<spl_conqueror::BinaryOption *> partial_config;
        for (auto &&option : full_config) {
          if (helpers::contains(options_to_consider, *option)) {
            partial_config.push_back(option);
          }
        }
        if (!partial_config.empty()) {
          all_configs.insert(partial_config);
        }
      }
      break;
    }
    case operations_research::sat::INFEASIBLE:
      break;
    default:
      throw std::runtime_error("unknown status: " + std::to_string(status));
  }

  delete context;
  return all_configs;
}

spl_conqueror::BucketSession *OrToolsVariantGenerator::create_bucket_session() {
  return new OrToolsBucketSession(_vm);
}

}
