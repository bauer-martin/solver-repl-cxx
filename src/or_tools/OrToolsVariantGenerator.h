#ifndef OR_TOOLS_VARIANT_GENERATOR_H
#define OR_TOOLS_VARIANT_GENERATOR_H

#include "spl_conqueror/VariabilityModel.h"
#include "spl_conqueror/VariantGenerator.h"

namespace or_tools {

class OrToolsVariantGenerator final : public spl_conqueror::VariantGenerator {
 private:
  const spl_conqueror::VariabilityModel &_vm;
  uint _seed;

 public:
  explicit OrToolsVariantGenerator(const spl_conqueror::VariabilityModel &vm);
  void set_seed(uint seed);
  std::vector<spl_conqueror::BinaryOption *> *find_minimized_config(
      const std::vector<spl_conqueror::BinaryOption *> &config,
      const std::vector<spl_conqueror::BinaryOption *> &unwanted_options) override;
  std::vector<std::vector<spl_conqueror::BinaryOption *>> find_all_maximized_configs(
      const std::vector<spl_conqueror::BinaryOption *> &config,
      const std::vector<spl_conqueror::BinaryOption *> &unwanted_options) override;
  std::vector<std::vector<spl_conqueror::BinaryOption *>> generate_up_to_n_configs(int n) override;
  std::vector<spl_conqueror::BinaryOption *> *generate_config_without_option(
      const std::vector<spl_conqueror::BinaryOption *> &config,
      const spl_conqueror::BinaryOption &option_to_remove,
      std::vector<spl_conqueror::BinaryOption *> &removed_options) override;
  std::set<std::vector<spl_conqueror::BinaryOption *>> generate_all_variants(
      const std::vector<spl_conqueror::BinaryOption *> &options_to_consider) override;
  spl_conqueror::BucketSession *create_bucket_session() override;

 public:
  OrToolsVariantGenerator(const OrToolsVariantGenerator &other) = delete;
  OrToolsVariantGenerator(OrToolsVariantGenerator &&other) noexcept = delete;
  OrToolsVariantGenerator &operator=(const OrToolsVariantGenerator &other) = delete;
  OrToolsVariantGenerator &operator=(OrToolsVariantGenerator &&other) noexcept = delete;
};

}

#endif //OR_TOOLS_VARIANT_GENERATOR_H
