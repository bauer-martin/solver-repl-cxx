#include "OptiMathSatSatChecker.h"

#include "mathsat.h"
#include "OptiMathSatConstraintSystemContext.h"
#include "OptiMathSatHelper.h"
#include "utilities/Helpers.h"

namespace opti_math_sat {

OptiMathSatSatChecker::OptiMathSatSatChecker(OptiMathSatConstraintSystemContext &context)
    : _context(context) {
}

static void select_features_and_deselect_all_others(
    const OptiMathSatConstraintSystemContext &context,
    const std::vector<spl_conqueror::BinaryOption *> &selected_options) {
  const msat_env &env = context.get_environment();
  for (auto &&option : context.get_variability_model().get_binary_options()) {
    const msat_term &variable = context.option_to_var(*option);
    if (helpers::contains(selected_options, *option)) {
      msat_assert_formula(env, msat_make_equal(env, variable, msat_make_number(env, "1")));
    } else {
      msat_assert_formula(env, msat_make_equal(env, variable, msat_make_number(env, "0")));
    }
  }
}

bool OptiMathSatSatChecker::is_valid(const std::vector<spl_conqueror::BinaryOption *> &selected_options,
                                     bool is_partial_configuration) {
  _context.mark_checkpoint();
  const msat_env &env = _context.get_environment();

  if (is_partial_configuration) {
    select_features(_context, selected_options);
  } else {
    select_features_and_deselect_all_others(_context, selected_options);
  }
  msat_result status = msat_solve(env);
  if (status == MSAT_UNKNOWN) {
    throw std::runtime_error("unknown status: " + std::to_string(status));
  }

  _context.reset_to_last_checkpoint();
  return status == MSAT_SAT;
}

}
