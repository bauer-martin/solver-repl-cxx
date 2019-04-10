#ifndef GLOBAL_CONTEXT_H
#define GLOBAL_CONTEXT_H

#include "option_coding/OptionCoding.h"
#include "spl_conqueror/BucketSession.h"
#include "spl_conqueror/SatChecker.h"
#include "spl_conqueror/SolverFacade.h"
#include "spl_conqueror/VariabilityModel.h"
#include "spl_conqueror/VariantGenerator.h"

namespace utilities {

class GlobalContext final {
 private:
  option_coding::OptionCoding *_option_coding;
  spl_conqueror::VariabilityModel *_variability_model;
  spl_conqueror::SolverFacade *_solver_facade;
  spl_conqueror::BucketSession *_bucket_session;

 public:
  GlobalContext();
  ~GlobalContext();
  option_coding::OptionCoding &get_option_coding() const;
  void set_option_coding(option_coding::OptionCoding *option_coding);
  spl_conqueror::VariabilityModel &get_variability_model() const;
  void set_variability_model(spl_conqueror::VariabilityModel *variability_model);
  spl_conqueror::SolverFacade &get_solver_facade() const;
  void set_solver_facade(spl_conqueror::SolverFacade *solver_facade);
  spl_conqueror::BucketSession *get_bucket_session() const;
  void set_bucket_session(spl_conqueror::BucketSession *bucket_session);

 public:
  GlobalContext(const GlobalContext &other) = delete;
  GlobalContext(GlobalContext &&other) noexcept = delete;
  GlobalContext &operator=(const GlobalContext &other) = delete;
  GlobalContext &operator=(GlobalContext &&other) noexcept = delete;
};

}

#endif //GLOBAL_CONTEXT_H
