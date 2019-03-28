#ifndef OPTI_MATH_SAT_SAT_CHECKER_H
#define OPTI_MATH_SAT_SAT_CHECKER_H

#include "OptiMathSatConstraintSystemContext.h"
#include "spl_conqueror/SatChecker.h"
#include "spl_conqueror/VariabilityModel.h"

namespace opti_math_sat {

class OptiMathSatSatChecker final : public spl_conqueror::SatChecker {
 private:
  OptiMathSatConstraintSystemContext &_context;

 public:
  explicit OptiMathSatSatChecker(OptiMathSatConstraintSystemContext &context);
  bool is_valid(const std::vector<spl_conqueror::BinaryOption *> &selected_options,
                bool is_partial_configuration) override;

 public:
  OptiMathSatSatChecker(const OptiMathSatSatChecker &other) = delete;
  OptiMathSatSatChecker(OptiMathSatSatChecker &&other) noexcept = delete;
  OptiMathSatSatChecker &operator=(const OptiMathSatSatChecker &other) = delete;
  OptiMathSatSatChecker &operator=(OptiMathSatSatChecker &&other) noexcept = delete;
};

}

#endif //OPTI_MATH_SAT_SAT_CHECKER_H
