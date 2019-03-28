#ifndef OPTI_MATH_SAT_SOLVER_FACTORY_H
#define OPTI_MATH_SAT_SOLVER_FACTORY_H

#include "spl_conqueror/SolverFactory.h"
#include "spl_conqueror/VariabilityModel.h"

namespace opti_math_sat {

class OptiMathSatConstraintSystemContext;

class OptiMathSatSolverFactory final : public spl_conqueror::SolverFactory {
 private:
  OptiMathSatConstraintSystemContext *_context;

 public:
  explicit OptiMathSatSolverFactory(const spl_conqueror::VariabilityModel &vm);
  ~OptiMathSatSolverFactory() override;
  spl_conqueror::SatChecker *make_sat_checker() override;
  spl_conqueror::VariantGenerator *make_variant_generator() override;

 public:
  OptiMathSatSolverFactory(const OptiMathSatSolverFactory &other) = delete;
  OptiMathSatSolverFactory(OptiMathSatSolverFactory &&other) noexcept = delete;
  OptiMathSatSolverFactory &operator=(const OptiMathSatSolverFactory &other) = delete;
  OptiMathSatSolverFactory &operator=(OptiMathSatSolverFactory &&other) noexcept = delete;
};

}

#endif //OPTI_MATH_SAT_SOLVER_FACTORY_H
