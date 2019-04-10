#include "or_tools/OrToolsSolverFacade.h"

#include "OrToolsSatChecker.h"
#include "OrToolsVariantGenerator.h"
#include "utilities/SolverParameterKeys.h"

namespace or_tools {

OrToolsSolverFacade::OrToolsSolverFacade(const spl_conqueror::VariabilityModel &vm)
    : _vm(vm), _sat_checker(nullptr), _variant_generator(nullptr), _seed(1) {
}

OrToolsSolverFacade::~OrToolsSolverFacade() {
  delete _sat_checker;
  delete _variant_generator;
}

void OrToolsSolverFacade::set_parameters(const std::map<std::string, std::string> &parameters) {
  auto search = parameters.find(utilities::SolverParameterKeys::random_seed);
  if (search != parameters.end()) {
    _seed = std::stoi(parameters.at(utilities::SolverParameterKeys::random_seed));
  }
  apply_parameters();
}

void OrToolsSolverFacade::apply_parameters() {
  if (!_variant_generator) return;
  auto *vg = (OrToolsVariantGenerator *) _variant_generator;
  vg->set_seed(_seed);
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
    apply_parameters();
  }
  return *_variant_generator;
}

}
