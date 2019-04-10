#include "or_tools/OrToolsSolverFacade.h"

#include "OrToolsSatChecker.h"
#include "OrToolsVariantGenerator.h"

namespace or_tools {

OrToolsSolverFacade::OrToolsSolverFacade(const spl_conqueror::VariabilityModel &vm)
    : _vm(vm), _sat_checker(nullptr), _variant_generator(nullptr) {
}

OrToolsSolverFacade::~OrToolsSolverFacade() {
  delete _sat_checker;
  delete _variant_generator;
}

void OrToolsSolverFacade::set_parameters(const std::map<std::string, std::string> &parameters) {
}

spl_conqueror::SatChecker &OrToolsSolverFacade::get_sat_checker() {
  if (!_sat_checker) {
    _sat_checker = new OrToolsSatChecker(_vm);
  }
  return *_sat_checker;
}

spl_conqueror::VariantGenerator &OrToolsSolverFacade::get_variant_generator() {
  if (!_variant_generator) {
    _variant_generator = new OrToolsVariantGenerator(_vm);
  }
  return *_variant_generator;
}

}
