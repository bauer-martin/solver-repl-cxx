#ifndef OR_TOOLS_BUCKET_SESSION_H
#define OR_TOOLS_BUCKET_SESSION_H

#include <map>
#include <vector>

#include "spl_conqueror/BinaryOption.h"
#include "spl_conqueror/BucketSession.h"
#include "spl_conqueror/VariabilityModel.h"

namespace or_tools {

class OrToolsBucketSession final : public spl_conqueror::BucketSession {
 private:
  const spl_conqueror::VariabilityModel &_vm;
  std::map<int, std::vector<std::vector<spl_conqueror::BinaryOption *>>> _buckets;
  std::vector<spl_conqueror::BinaryOption *> *generate_config(
      int selected_options_count,
      const std::vector<std::vector<spl_conqueror::BinaryOption *>> &feature_ranking,
      const std::vector<std::vector<spl_conqueror::BinaryOption *>> &excluded_configs);
  std::vector<spl_conqueror::BinaryOption *> *get_small_weight_config(
      int selected_options_count,
      const std::vector<std::vector<spl_conqueror::BinaryOption *>> &feature_ranking,
      const std::vector<std::vector<spl_conqueror::BinaryOption *>> &excluded_configs);

 public:
  explicit OrToolsBucketSession(const spl_conqueror::VariabilityModel &vm);
  ~OrToolsBucketSession() override;
  std::vector<spl_conqueror::BinaryOption *> *generate_config(
      int selected_options_count,
      const std::vector<std::vector<spl_conqueror::BinaryOption *>> &feature_ranking) override;
};

}

#endif //OR_TOOLS_BUCKET_SESSION_H
