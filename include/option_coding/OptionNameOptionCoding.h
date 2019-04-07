#ifndef OPTION_NAME_OPTION_CODING_H
#define OPTION_NAME_OPTION_CODING_H

#include "option_coding/OptionCoding.h"

namespace option_coding {

class OptionNameOptionCoding : public OptionCoding {
 public:
  explicit OptionNameOptionCoding(const spl_conqueror::VariabilityModel &vm);
  ~OptionNameOptionCoding() override;
  std::vector<spl_conqueror::BinaryOption *> decode_binary_options(const std::string &str) const override;
  std::string encode_binary_options(const std::vector<spl_conqueror::BinaryOption *> &options) const override;
  std::string encode_binary_options_vector(
      const std::vector<std::vector<spl_conqueror::BinaryOption *>> &configs) const override;
  std::string encode_binary_options_set(
      const std::set<std::vector<spl_conqueror::BinaryOption *>> &configs) const override;

 public:
  OptionNameOptionCoding(const OptionNameOptionCoding &other) = delete;
  OptionNameOptionCoding(OptionNameOptionCoding &&other) noexcept = delete;
  OptionNameOptionCoding &operator=(const OptionNameOptionCoding &other) = delete;
  OptionNameOptionCoding &operator=(OptionNameOptionCoding &&other) noexcept = delete;
};

}

#endif //OPTION_NAME_OPTION_CODING_H
