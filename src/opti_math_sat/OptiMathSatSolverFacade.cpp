#include "opti_math_sat/OptiMathSatSolverFacade.h"

#include "OptiMathSatConstraintSystemContext.h"
#include "OptiMathSatSatChecker.h"
#include "OptiMathSatVariantGenerator.h"

namespace opti_math_sat {

OptiMathSatSolverFacade::OptiMathSatSolverFacade(const spl_conqueror::VariabilityModel &vm)
    : _context(OptiMathSatConstraintSystemContext::make_from(vm)),
      _sat_checker(nullptr),
      _variant_generator(nullptr) {
}

OptiMathSatSolverFacade::~OptiMathSatSolverFacade() {
  delete _context;
  delete _sat_checker;
  delete _variant_generator;
}

spl_conqueror::SatChecker &OptiMathSatSolverFacade::get_sat_checker() {
  if (!_sat_checker) {
    _sat_checker = new OptiMathSatSatChecker(*_context);
  }
  return *_sat_checker;
}

spl_conqueror::VariantGenerator &OptiMathSatSolverFacade::get_variant_generator() {
  if (!_variant_generator) {
    _variant_generator = new OptiMathSatVariantGenerator(*_context);
  }
  return *_variant_generator;
}

}
