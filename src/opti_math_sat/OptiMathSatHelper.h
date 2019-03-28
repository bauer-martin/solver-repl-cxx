#ifndef OPTI_MATH_SAT_HELPER_H
#define OPTI_MATH_SAT_HELPER_H

#include <vector>

#include "mathsat.h"
#include "OptiMathSatConstraintSystemContext.h"
#include "spl_conqueror/BinaryOption.h"

namespace opti_math_sat {

void select_features(const OptiMathSatConstraintSystemContext &context,
                     const std::vector<spl_conqueror::BinaryOption *> &selected_options);

std::vector<spl_conqueror::BinaryOption *> to_binary_options(const OptiMathSatConstraintSystemContext &context,
                                                             const msat_model &model);

}

#endif //OPTI_MATH_SAT_HELPER_H
