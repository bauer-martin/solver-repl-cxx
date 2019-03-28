#include "opti_math_sat/OptiMathSatSolverFactory.h"

#include "OptiMathSatConstraintSystemContext.h"
#include "OptiMathSatSatChecker.h"
#include "OptiMathSatVariantGenerator.h"

namespace opti_math_sat {

OptiMathSatSolverFactory::OptiMathSatSolverFactory(const spl_conqueror::VariabilityModel &vm)
    : _context(OptiMathSatConstraintSystemContext::make_from(vm)) {
}

OptiMathSatSolverFactory::~OptiMathSatSolverFactory() {
  delete _context;
}

spl_conqueror::SatChecker *OptiMathSatSolverFactory::make_sat_checker() {
  return new OptiMathSatSatChecker(*_context);
}

spl_conqueror::VariantGenerator *OptiMathSatSolverFactory::make_variant_generator() {
  return new OptiMathSatVariantGenerator(*_context);
}

}
