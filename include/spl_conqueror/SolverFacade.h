#ifndef SOLVER_FACADE_H
#define SOLVER_FACADE_H

#include <map>

#include "spl_conqueror/SatChecker.h"
#include "spl_conqueror/VariantGenerator.h"

namespace spl_conqueror {

class SolverFacade {
 protected:
  SolverFacade();

 public:
  virtual ~SolverFacade();
  virtual void set_parameters(const std::map<std::string, std::string> &parameters) = 0;
  virtual SatChecker &get_sat_checker() = 0;
  virtual VariantGenerator &get_variant_generator() = 0;

 public:
  SolverFacade(const SolverFacade &other) = delete;
  SolverFacade(SolverFacade &&other) noexcept = delete;
  SolverFacade &operator=(const SolverFacade &other) = delete;
  SolverFacade &operator=(SolverFacade &&other) noexcept = delete;
};

}

#endif //SOLVER_FACADE_H
