#ifndef OPTI_MATH_SAT_SOLVER_FACADE_H
#define OPTI_MATH_SAT_SOLVER_FACADE_H

#include "spl_conqueror/SolverFacade.h"
#include "spl_conqueror/VariabilityModel.h"

namespace opti_math_sat {

class OptiMathSatConstraintSystemContext;

class OptiMathSatSolverFacade final : public spl_conqueror::SolverFacade {
 private:
  OptiMathSatConstraintSystemContext *_context;
  spl_conqueror::SatChecker *_sat_checker;
  spl_conqueror::VariantGenerator *_variant_generator;

 public:
  explicit OptiMathSatSolverFacade(const spl_conqueror::VariabilityModel &vm);
  ~OptiMathSatSolverFacade() override;
  spl_conqueror::SatChecker &get_sat_checker() override;
  spl_conqueror::VariantGenerator &get_variant_generator() override;

 public:
  OptiMathSatSolverFacade(const OptiMathSatSolverFacade &other) = delete;
  OptiMathSatSolverFacade(OptiMathSatSolverFacade &&other) noexcept = delete;
  OptiMathSatSolverFacade &operator=(const OptiMathSatSolverFacade &other) = delete;
  OptiMathSatSolverFacade &operator=(OptiMathSatSolverFacade &&other) noexcept = delete;
};

}

#endif //OPTI_MATH_SAT_SOLVER_FACADE_H
