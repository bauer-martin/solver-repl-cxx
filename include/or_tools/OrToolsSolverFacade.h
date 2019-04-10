#ifndef OR_TOOLS_SOLVER_FACADE_H
#define OR_TOOLS_SOLVER_FACADE_H

#include "spl_conqueror/SolverFacade.h"
#include "spl_conqueror/VariabilityModel.h"

namespace or_tools {

class OrToolsSolverFacade final : public spl_conqueror::SolverFacade {
 private:
  const spl_conqueror::VariabilityModel &_vm;
  spl_conqueror::SatChecker *_sat_checker;
  spl_conqueror::VariantGenerator *_variant_generator;

 public:
  explicit OrToolsSolverFacade(const spl_conqueror::VariabilityModel &vm);
  ~OrToolsSolverFacade() override;
  spl_conqueror::SatChecker &get_sat_checker() override;
  spl_conqueror::VariantGenerator &get_variant_generator() override;

 public:
  OrToolsSolverFacade(const OrToolsSolverFacade &other) = delete;
  OrToolsSolverFacade(OrToolsSolverFacade &&other) noexcept = delete;
  OrToolsSolverFacade &operator=(const OrToolsSolverFacade &other) = delete;
  OrToolsSolverFacade &operator=(OrToolsSolverFacade &&other) noexcept = delete;
};

}

#endif //OR_TOOLS_SOLVER_FACADE_H
