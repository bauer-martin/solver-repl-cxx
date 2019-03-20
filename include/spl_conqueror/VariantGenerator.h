#ifndef VARIANT_GENERATOR_H
#define VARIANT_GENERATOR_H

#include <set>
#include <vector>

#include "spl_conqueror/BinaryOption.h"
#include "spl_conqueror/BucketSession.h"

namespace spl_conqueror {

class VariantGenerator {
 protected:
  VariantGenerator();

 public:
  virtual ~VariantGenerator();
  virtual std::vector<BinaryOption *> *find_minimized_config(const std::vector<BinaryOption *> &config,
                                                             const std::vector<BinaryOption *> &unwanted_options) = 0;

  virtual std::vector<std::vector<BinaryOption *>> find_all_maximized_configs(
      const std::vector<BinaryOption *> &config,
      const std::vector<BinaryOption *> &unwanted_options) = 0;

  virtual std::vector<std::vector<BinaryOption *>> generate_up_to_n_configs(int n) = 0;

  virtual std::vector<BinaryOption *> *generate_config_without_option(const std::vector<BinaryOption *> &config,
                                                                      const BinaryOption &option_to_remove,
                                                                      std::vector<BinaryOption *> &removed_options) = 0;

  virtual std::set<std::vector<BinaryOption *>> generate_all_variants(
      const std::vector<BinaryOption *> &options_to_consider) = 0;

  virtual BucketSession *create_bucket_session() = 0;

 public:
  VariantGenerator(const VariantGenerator &other) = delete;
  VariantGenerator(VariantGenerator &&other) noexcept = delete;
  VariantGenerator &operator=(const VariantGenerator &other) = delete;
  VariantGenerator &operator=(VariantGenerator &&other) noexcept = delete;
};

}

#endif //VARIANT_GENERATOR_H
