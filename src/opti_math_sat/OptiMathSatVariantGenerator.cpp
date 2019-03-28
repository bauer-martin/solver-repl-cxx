#include "OptiMathSatVariantGenerator.h"

#include "optimathsat.h"
#include "OptiMathSatBucketSession.h"
#include "OptiMathSatHelper.h"
#include "utilities/Helpers.h"

namespace opti_math_sat {

OptiMathSatVariantGenerator::OptiMathSatVariantGenerator(OptiMathSatConstraintSystemContext &context)
    : _context(context) {
}

static msat_term add_option_weighting(
    const OptiMathSatConstraintSystemContext &context,
    const std::function<const char *(spl_conqueror::BinaryOption *)> &weighting_function) {
  const msat_env &env = context.get_environment();
  msat_term cost_term = msat_make_number(env, "0");
  for (auto &&option : context.get_variability_model().get_binary_options()) {
    const char *num_repr = weighting_function(option);
    msat_term term = msat_make_times(env, msat_make_number(env, num_repr), context.option_to_var(*option));
    cost_term = msat_make_plus(env, cost_term, term);
  }
  return cost_term;
}

static bool find_optimal_cost(const msat_env &env, const msat_term &cost_term, char *&cost_value_repr) {
  msat_term none;
  MSAT_MAKE_ERROR_TERM(none);
  // minimize within bounds of -inf to +inf
  msat_objective objective = msat_make_minimize(env, cost_term, none, none);
  msat_assert_objective(env, objective);
  msat_solve(env);
  bool has_found_optimal_cost = false;
  msat_opt_result status = msat_objective_result(env, objective);
  switch (status) {
    case MSAT_OPT_SAT_OPTIMAL: {
      msat_term cost_value = msat_objective_value_term(env, objective, MSAT_OPTIMUM, none, none);
      cost_value_repr = msat_term_repr(cost_value);
      has_found_optimal_cost = true;
      break;
    }
    case MSAT_OPT_UNSAT:
      break;
    default:
      throw std::runtime_error("unknown status: " + std::to_string(status));
  }
  msat_destroy_objective(env, objective);
  return has_found_optimal_cost;
}

static void find_solutions(const OptiMathSatConstraintSystemContext &context,
                           const msat_env &env,
                           std::vector<std::vector<spl_conqueror::BinaryOption *>> &configs,
                           int limit) {
  int solution_count = 0;
  msat_result status = msat_solve(env);
  while (status == MSAT_SAT) {
    msat_model model = msat_get_model(env);
    msat_term assignment = msat_make_true(env);
    std::vector<spl_conqueror::BinaryOption *> config;
    for (auto &&option : context.get_variability_model().get_binary_options()) {
      const msat_term &term = context.option_to_var(*option);
      msat_term value = msat_model_eval(model, term);
      assignment = msat_make_and(env,
                                 assignment,
                                 msat_make_eq(env, term, value));
      char *s = msat_term_repr(value);
      std::string value_as_string = s;
      msat_free(s);
      if (value_as_string == "1") {
        config.push_back(option);
      }
    }
    configs.push_back(config);
    ++solution_count;
    msat_destroy_model(model);
    if (limit > 0 && solution_count >= limit) break;

    // prevent next model from using the same assignment as a previous model
    msat_assert_formula(env, msat_make_not(env, assignment));
    status = msat_solve(env);
  }
  if (status != MSAT_SAT && status != MSAT_UNSAT) {
    throw std::runtime_error("unknown status: " + std::to_string(status));
  }
}

std::vector<spl_conqueror::BinaryOption *> *OptiMathSatVariantGenerator::find_minimized_config(
    const std::vector<spl_conqueror::BinaryOption *> &config,
    const std::vector<spl_conqueror::BinaryOption *> &unwanted_options) {
  _context.mark_checkpoint();
  const msat_env &env = _context.get_environment();

  select_features(_context, config);
  msat_term cost_term = add_option_weighting(
      _context,
      [&unwanted_options, &config](spl_conqueror::BinaryOption *option) -> const char * {
        return helpers::contains(unwanted_options, *option)
                   && !helpers::contains(config, *option) ? "100" : "1";
      });

  char *cost_value_repr = nullptr;
  bool has_found_optimal_cost = find_optimal_cost(env, cost_term, cost_value_repr);
  std::vector<spl_conqueror::BinaryOption *> *minimal_config = nullptr;
  if (has_found_optimal_cost) {
    msat_model model = msat_get_model(env);
    minimal_config = new std::vector<spl_conqueror::BinaryOption *>(to_binary_options(_context, model));
    msat_destroy_model(model);
    msat_free(cost_value_repr);
  }

  _context.reset_to_last_checkpoint();
  return minimal_config;
}

std::vector<std::vector<spl_conqueror::BinaryOption *>> OptiMathSatVariantGenerator::find_all_maximized_configs(
    const std::vector<spl_conqueror::BinaryOption *> &config,
    const std::vector<spl_conqueror::BinaryOption *> &unwanted_options) {
  _context.mark_checkpoint();
  const msat_env &env = _context.get_environment();

  select_features(_context, config);
  msat_term cost_term = add_option_weighting(
      _context,
      [&unwanted_options, &config](spl_conqueror::BinaryOption *option) -> const char * {
        return helpers::contains(unwanted_options, *option)
                   && !helpers::contains(config, *option) ? "100" : "-1";
      });

  char *cost_value_repr = nullptr;
  bool has_found_optimal_cost = find_optimal_cost(env, cost_term, cost_value_repr);
  std::vector<std::vector<spl_conqueror::BinaryOption *>> all_configs;
  if (has_found_optimal_cost) {
    msat_assert_formula(env, msat_make_equal(env, cost_term, msat_make_number(env, cost_value_repr)));
    find_solutions(_context, env, all_configs, -1);
    msat_free(cost_value_repr);
  }

  _context.reset_to_last_checkpoint();
  return all_configs;
}

std::vector<std::vector<spl_conqueror::BinaryOption *>> OptiMathSatVariantGenerator::generate_up_to_n_configs(int n) {
  _context.mark_checkpoint();
  const msat_env &env = _context.get_environment();

  std::vector<std::vector<spl_conqueror::BinaryOption *>> all_configs;
  find_solutions(_context, env, all_configs, n);

  _context.reset_to_last_checkpoint();
  return all_configs;
}

std::vector<spl_conqueror::BinaryOption *> *OptiMathSatVariantGenerator::generate_config_without_option(
    const std::vector<spl_conqueror::BinaryOption *> &config,
    const spl_conqueror::BinaryOption &option_to_remove,
    std::vector<spl_conqueror::BinaryOption *> &removed_options) {
  _context.mark_checkpoint();
  const msat_env &env = _context.get_environment();

  msat_assert_formula(env, msat_make_equal(env, _context.option_to_var(option_to_remove), msat_make_number(env, "0")));
  msat_term cost_term = add_option_weighting(
      _context,
      [&config](spl_conqueror::BinaryOption *option) -> const char * {
        return helpers::contains(config, *option) ? "-1000" : "1000";
      });

  char *cost_value_repr = nullptr;
  bool has_found_optimal_cost = find_optimal_cost(env, cost_term, cost_value_repr);
  std::vector<spl_conqueror::BinaryOption *> *new_config = nullptr;
  if (has_found_optimal_cost) {
    msat_model model = msat_get_model(env);
    new_config = new std::vector<spl_conqueror::BinaryOption *>(to_binary_options(_context, model));
    msat_destroy_model(model);
    msat_free(cost_value_repr);
  }

  _context.reset_to_last_checkpoint();
  return new_config;
}

std::set<std::vector<spl_conqueror::BinaryOption *>> OptiMathSatVariantGenerator::generate_all_variants(
    const std::vector<spl_conqueror::BinaryOption *> &options_to_consider) {
  _context.mark_checkpoint();
  const msat_env &env = _context.get_environment();

  std::set<std::vector<spl_conqueror::BinaryOption *>> configs;
  msat_result status = msat_solve(env);
  while (status == MSAT_SAT) {
    msat_model model = msat_get_model(env);
    msat_term assignment = msat_make_true(env);
    std::vector<spl_conqueror::BinaryOption *> config;
    for (auto &&option : _context.get_variability_model().get_binary_options()) {
      const msat_term &term = _context.option_to_var(*option);
      msat_term value = msat_model_eval(model, term);
      assignment = msat_make_and(env,
                                 assignment,
                                 msat_make_eq(env, term, value));
      char *s = msat_term_repr(value);
      std::string value_as_string = s;
      msat_free(s);
      if (value_as_string == "1" && helpers::contains(options_to_consider, *option)) {
        config.push_back(option);
      }
    }
    if (!config.empty()) {
      configs.insert(config);
    }
    msat_destroy_model(model);

    // prevent next model from using the same assignment as a previous model
    msat_assert_formula(env, msat_make_not(env, assignment));
    status = msat_solve(env);
  }
  if (status != MSAT_UNSAT) {
    throw std::runtime_error("unknown status: " + std::to_string(status));
  }

  _context.reset_to_last_checkpoint();
  return configs;
}

spl_conqueror::BucketSession *OptiMathSatVariantGenerator::create_bucket_session() {
  return new OptiMathSatBucketSession(_context);
}

}
