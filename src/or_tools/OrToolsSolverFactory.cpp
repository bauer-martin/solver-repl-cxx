#include "or_tools/OrToolsSolverFactory.h"

#include "OrToolsSatChecker.h"
#include "OrToolsVariantGenerator.h"

namespace or_tools {

OrToolsSolverFactory::OrToolsSolverFactory(const spl_conqueror::VariabilityModel &vm) : _vm(vm) {
}

OrToolsSolverFactory::~OrToolsSolverFactory() = default;

spl_conqueror::SatChecker *OrToolsSolverFactory::make_sat_checker() {
  return new OrToolsSatChecker(_vm);
}

spl_conqueror::VariantGenerator *OrToolsSolverFactory::make_variant_generator() {
  return new OrToolsVariantGenerator(_vm);
}

}
