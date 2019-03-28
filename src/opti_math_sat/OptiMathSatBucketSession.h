#ifndef OPTI_MATH_SAT_BUCKET_SESSION_H
#define OPTI_MATH_SAT_BUCKET_SESSION_H

#include <map>
#include <vector>

#include "OptiMathSatConstraintSystemContext.h"
#include "spl_conqueror/BinaryOption.h"
#include "spl_conqueror/BucketSession.h"

namespace opti_math_sat {

class OptiMathSatBucketSession final : public spl_conqueror::BucketSession {
 private:
  OptiMathSatConstraintSystemContext &_context;
  std::map<int, std::vector<std::vector<spl_conqueror::BinaryOption *>>> _buckets;
  std::vector<spl_conqueror::BinaryOption *> *generate_config(
      int selected_options_count,
      const std::vector<std::vector<spl_conqueror::BinaryOption *>> &feature_ranking,
      const std::vector<std::vector<spl_conqueror::BinaryOption *>> &excluded_configs);
  std::vector<spl_conqueror::BinaryOption *> *get_small_weight_config(
      const std::vector<std::vector<spl_conqueror::BinaryOption *>> &feature_ranking);

 public:
  explicit OptiMathSatBucketSession(OptiMathSatConstraintSystemContext &context);
  ~OptiMathSatBucketSession() override;
  std::vector<spl_conqueror::BinaryOption *> *generate_config(
      int selected_options_count,
      const std::vector<std::vector<spl_conqueror::BinaryOption *>> &feature_ranking) override;
};

}

#endif //OPTI_MATH_SAT_BUCKET_SESSION_H
