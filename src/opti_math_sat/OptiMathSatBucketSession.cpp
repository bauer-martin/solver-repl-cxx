#include "OptiMathSatBucketSession.h"

#include <string>

#include "OptiMathSatHelper.h"
#include "utilities/Helpers.h"

namespace opti_math_sat {

OptiMathSatBucketSession::OptiMathSatBucketSession(OptiMathSatConstraintSystemContext &context)
    : _context(context) {
}

OptiMathSatBucketSession::~OptiMathSatBucketSession() = default;

std::vector<spl_conqueror::BinaryOption *> *OptiMathSatBucketSession::generate_config(
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

std::vector<spl_conqueror::BinaryOption *> *OptiMathSatBucketSession::generate_config(
    int selected_options_count,
    const std::vector<std::vector<spl_conqueror::BinaryOption *>> &feature_ranking,
    const std::vector<std::vector<spl_conqueror::BinaryOption *>> &excluded_configs) {
  _context.mark_checkpoint();
  const msat_env &env = _context.get_environment();

  // there should be exactly selectedOptionsCount features selected
  msat_term cost_term = msat_make_number(env, "0");
  for (auto &&option : _context.get_variability_model().get_binary_options()) {
    cost_term = msat_make_plus(env, cost_term, _context.option_to_var(*option));
  }
  const msat_term &formula = msat_make_equal(env,
                                             cost_term,
                                             msat_make_number(env, std::to_string(selected_options_count).c_str()));
  msat_assert_formula(env, formula);

  // excluded configurations should not be considered as a solution
  for (auto &&excluded_config : excluded_configs) {
    msat_term and_term = msat_make_true(env);
    for (auto &&option : _context.get_variability_model().get_binary_options()) {
      const msat_term &variable = _context.option_to_var(*option);
      if (helpers::contains(excluded_config, *option)) {
        and_term = msat_make_and(env, and_term, msat_make_equal(env, variable, msat_make_number(env, "1")));
      } else {
        and_term = msat_make_and(env, and_term, msat_make_equal(env, variable, msat_make_number(env, "0")));
      }
    }
    msat_assert_formula(env, msat_make_not(env, and_term));
  }

  // if we have a feature ranking, we can use it to approximate the optimal solution
  std::vector<spl_conqueror::BinaryOption *> *approximate_optimal = get_small_weight_config(feature_ranking);
  std::vector<spl_conqueror::BinaryOption *> *result = nullptr;
  if (approximate_optimal) {
    result = approximate_optimal;
  } else {
    msat_result status = msat_solve(env);
    if (status == MSAT_SAT) {
      msat_model model = msat_get_model(env);
      result = new std::vector<spl_conqueror::BinaryOption *>(to_binary_options(_context, model));
      msat_destroy_model(model);
    } else if (status == MSAT_UNKNOWN) {
      throw std::runtime_error("unknown status: " + std::to_string(status));
    }
  }

  _context.reset_to_last_checkpoint();
  return result;
}

std::vector<spl_conqueror::BinaryOption *> *OptiMathSatBucketSession::get_small_weight_config(
    const std::vector<std::vector<spl_conqueror::BinaryOption *>> &feature_ranking) {
  const msat_env &env = _context.get_environment();
  std::vector<spl_conqueror::BinaryOption *> *result = nullptr;
  for (auto &&config : feature_ranking) {
    _context.mark_checkpoint();

    // force features to be selected
    select_features(_context, config);

    // check if satisfiable
    msat_result status = msat_solve(env);
    if (status == MSAT_SAT) {
      msat_model model = msat_get_model(env);
      result = new std::vector<spl_conqueror::BinaryOption *>(to_binary_options(_context, model));
      msat_destroy_model(model);
    } else if (status == MSAT_UNKNOWN) {
      throw std::runtime_error("unknown status: " + std::to_string(status));
    }

    _context.reset_to_last_checkpoint();
    // stop if solution has been found
    if (result) {
      break;
    }
  }
  return result;
}

}
