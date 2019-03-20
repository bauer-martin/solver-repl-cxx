#include "utilities/GlobalContext.h"

#include <stdexcept>

namespace utilities {

GlobalContext::GlobalContext() : _variability_model(nullptr),
                                 _solver_factory(nullptr),
                                 _sat_checker(nullptr),
                                 _variant_generator(nullptr),
                                 _bucket_session(nullptr) {
}

GlobalContext::~GlobalContext() {
  delete _variability_model;
  delete _solver_factory;
  delete _sat_checker;
  delete _variant_generator;
  delete _bucket_session;
}

spl_conqueror::VariabilityModel &GlobalContext::get_variability_model() const {
  if (_variability_model) {
    return *_variability_model;
  } else {
    throw std::runtime_error("no variability model has been set");
  }
}

void GlobalContext::set_variability_model(spl_conqueror::VariabilityModel *variability_model) {
  if (_variability_model) {
    throw std::runtime_error("changing the variability model is not supported");
  } else {
    _variability_model = variability_model;
  }
}

spl_conqueror::SolverFactory &GlobalContext::get_solver_factory() const {
  if (_solver_factory) {
    return *_solver_factory;
  } else {
    throw std::runtime_error("no solver factory has been set");
  }
}

void GlobalContext::set_solver_factory(spl_conqueror::SolverFactory *solver_factory) {
  delete _solver_factory;
  _solver_factory = solver_factory;
  delete _sat_checker;
  _sat_checker = nullptr;
  delete _variant_generator;
  _variant_generator = nullptr;
}

spl_conqueror::SatChecker &GlobalContext::get_sat_checker() {
  if (!_sat_checker) {
    _sat_checker = get_solver_factory().make_sat_checker();
  }
  return *_sat_checker;
}

spl_conqueror::VariantGenerator &GlobalContext::get_variant_generator() {
  if (!_variant_generator) {
    _variant_generator = get_solver_factory().make_variant_generator();
  }
  return *_variant_generator;
}

spl_conqueror::BucketSession *GlobalContext::get_bucket_session() const {
  return _bucket_session;
}

void GlobalContext::set_bucket_session(spl_conqueror::BucketSession *bucket_session) {
  delete _bucket_session;
  _bucket_session = bucket_session;
}

}
