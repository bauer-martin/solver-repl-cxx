#ifndef OPTI_MATH_SAT_VARIANT_GENERATOR_H
#define OPTI_MATH_SAT_VARIANT_GENERATOR_H

#include "OptiMathSatConstraintSystemContext.h"
#include "spl_conqueror/VariabilityModel.h"
#include "spl_conqueror/VariantGenerator.h"

namespace opti_math_sat {

class OptiMathSatVariantGenerator final : public spl_conqueror::VariantGenerator {
 private:
  OptiMathSatConstraintSystemContext &_context;

 public:
  explicit OptiMathSatVariantGenerator(OptiMathSatConstraintSystemContext &context);
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
  OptiMathSatVariantGenerator(const OptiMathSatVariantGenerator &other) = delete;
  OptiMathSatVariantGenerator(OptiMathSatVariantGenerator &&other) noexcept = delete;
  OptiMathSatVariantGenerator &operator=(const OptiMathSatVariantGenerator &other) = delete;
  OptiMathSatVariantGenerator &operator=(OptiMathSatVariantGenerator &&other) noexcept = delete;
};

}

#endif //OPTI_MATH_SAT_VARIANT_GENERATOR_H
