#include "opti_math_sat/OptiMathSatSolverFacade.h"

#include <stdexcept>

#include "OptiMathSatConstraintSystemContext.h"
#include "OptiMathSatSatChecker.h"
#include "OptiMathSatVariantGenerator.h"
#include "utilities/SolverParameterKeys.h"

namespace opti_math_sat {

OptiMathSatSolverFacade::OptiMathSatSolverFacade(const spl_conqueror::VariabilityModel &vm)
    : _vm(vm),
      _context(nullptr),
      _sat_checker(nullptr),
      _variant_generator(nullptr),
      _seed(1) {
}

OptiMathSatSolverFacade::~OptiMathSatSolverFacade() {
  delete _context;
  delete _sat_checker;
  delete _variant_generator;
}

void OptiMathSatSolverFacade::set_parameters(const std::map<std::string, std::string> &parameters) {
  if (_context) {
    throw std::runtime_error("OptiMathSat can not change parameters at runtime");
  }
  auto search = parameters.find(utilities::SolverParameterKeys::random_seed);
  if (search != parameters.end()) {
    _seed = std::stoi(parameters.at(utilities::SolverParameterKeys::random_seed));
  }
}

spl_conqueror::SatChecker &OptiMathSatSolverFacade::get_sat_checker() {
  if (!_sat_checker) {
    if (!_context) {
      _context = OptiMathSatConstraintSystemContext::make_from(_vm, _seed);
    }
    _sat_checker = new OptiMathSatSatChecker(*_context);
  }
  return *_sat_checker;
}

spl_conqueror::VariantGenerator &OptiMathSatSolverFacade::get_variant_generator() {
  if (!_variant_generator) {
    if (!_context) {
      _context = OptiMathSatConstraintSystemContext::make_from(_vm, _seed);
    }
    _variant_generator = new OptiMathSatVariantGenerator(*_context);
  }
  return *_variant_generator;
}

}
