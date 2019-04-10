#include "utilities/GlobalContext.h"

#include <stdexcept>

namespace utilities {

GlobalContext::GlobalContext() : _option_coding(nullptr),
                                 _variability_model(nullptr),
                                 _solver_facade(nullptr),
                                 _bucket_session(nullptr) {
}

GlobalContext::~GlobalContext() {
  delete _option_coding;
  delete _variability_model;
  delete _solver_facade;
  delete _bucket_session;
}

option_coding::OptionCoding &GlobalContext::get_option_coding() const {
  if (_option_coding) {
    return *_option_coding;
  } else {
    throw std::runtime_error("no coding strategy has been set");
  }
}

void GlobalContext::set_option_coding(option_coding::OptionCoding *option_coding) {
  delete _option_coding;
  _option_coding = option_coding;
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

spl_conqueror::SolverFacade &GlobalContext::get_solver_facade() const {
  if (_solver_facade) {
    return *_solver_facade;
  } else {
    throw std::runtime_error("no solver facade has been set");
  }
}

void GlobalContext::set_solver_facade(spl_conqueror::SolverFacade *solver_facade) {
  delete _solver_facade;
  _solver_facade = solver_facade;
}

spl_conqueror::BucketSession *GlobalContext::get_bucket_session() const {
  return _bucket_session;
}

void GlobalContext::set_bucket_session(spl_conqueror::BucketSession *bucket_session) {
  delete _bucket_session;
  _bucket_session = bucket_session;
}

}
