#ifndef GLOBAL_CONTEXT_H
#define GLOBAL_CONTEXT_H

#include "spl_conqueror/BucketSession.h"
#include "spl_conqueror/SatChecker.h"
#include "spl_conqueror/SolverFactory.h"
#include "spl_conqueror/VariabilityModel.h"
#include "spl_conqueror/VariantGenerator.h"

namespace utilities {

class GlobalContext final {
 private:
  spl_conqueror::VariabilityModel *_variability_model;
  spl_conqueror::SolverFactory *_solver_factory;
  spl_conqueror::SatChecker *_sat_checker;
  spl_conqueror::VariantGenerator *_variant_generator;
  spl_conqueror::BucketSession *_bucket_session;

 public:
  GlobalContext();
  ~GlobalContext();
  spl_conqueror::VariabilityModel &get_variability_model() const;
  void set_variability_model(spl_conqueror::VariabilityModel *variability_model);
  spl_conqueror::SolverFactory &get_solver_factory() const;
  void set_solver_factory(spl_conqueror::SolverFactory *solver_factory);
  spl_conqueror::SatChecker &get_sat_checker();
  spl_conqueror::VariantGenerator &get_variant_generator();
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
