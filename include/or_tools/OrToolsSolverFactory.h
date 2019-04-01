#ifndef OR_TOOLS_SOLVER_FACTORY_H
#define OR_TOOLS_SOLVER_FACTORY_H

#include "spl_conqueror/SolverFactory.h"
#include "spl_conqueror/VariabilityModel.h"

namespace or_tools {

class OrToolsSolverFactory final : public spl_conqueror::SolverFactory {
 private:
  const spl_conqueror::VariabilityModel &_vm;

 public:
  explicit OrToolsSolverFactory(const spl_conqueror::VariabilityModel &vm);
  ~OrToolsSolverFactory() override;
  spl_conqueror::SatChecker *make_sat_checker() override;
  spl_conqueror::VariantGenerator *make_variant_generator() override;

 public:
  OrToolsSolverFactory(const OrToolsSolverFactory &other) = delete;
  OrToolsSolverFactory(OrToolsSolverFactory &&other) noexcept = delete;
  OrToolsSolverFactory &operator=(const OrToolsSolverFactory &other) = delete;
  OrToolsSolverFactory &operator=(OrToolsSolverFactory &&other) noexcept = delete;
};

}

#endif //OR_TOOLS_SOLVER_FACTORY_H
