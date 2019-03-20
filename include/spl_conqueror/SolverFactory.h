#ifndef SOLVER_FACTORY_H
#define SOLVER_FACTORY_H

#include "spl_conqueror/SatChecker.h"
#include "spl_conqueror/VariantGenerator.h"

namespace spl_conqueror {

class SolverFactory {
 protected:
  SolverFactory();

 public:
  virtual ~SolverFactory();
  virtual SatChecker *make_sat_checker() = 0;
  virtual VariantGenerator *make_variant_generator() = 0;

 public:
  SolverFactory(const SolverFactory &other) = delete;
  SolverFactory(SolverFactory &&other) noexcept = delete;
  SolverFactory &operator=(const SolverFactory &other) = delete;
  SolverFactory &operator=(SolverFactory &&other) noexcept = delete;
};

}

#endif //SOLVER_FACTORY_H
