#include "OptiMathSatHelper.h"

#include "utilities/Helpers.h"

namespace opti_math_sat {

void select_features(const OptiMathSatConstraintSystemContext &context,
                     const std::vector<spl_conqueror::BinaryOption *> &selected_options) {
  const msat_env &env = context.get_environment();
  for (auto &&option : selected_options) {
    const msat_term &variable = context.option_to_var(*option);
    msat_assert_formula(env, msat_make_equal(env, variable, msat_make_number(env, "1")));
  }
}

std::vector<spl_conqueror::BinaryOption *> to_binary_options(const OptiMathSatConstraintSystemContext &context,
                                                             const msat_model &model) {
  std::vector<spl_conqueror::BinaryOption *> config;
  for (auto &&option : context.get_variability_model().get_binary_options()) {
    const msat_term &term = context.option_to_var(*option);
    msat_term value = msat_model_eval(model, term);
    char *s = msat_term_repr(value);
    std::string value_as_string = s;
    msat_free(s);
    if (value_as_string == "1") {
      config.push_back(option);
    }
  }
  return config;
}

}
