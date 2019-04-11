#ifndef OPTION_NAME_OPTION_CODING_H
#define OPTION_NAME_OPTION_CODING_H

#include "option_coding/AbstractOptionCoding.h"

namespace option_coding {

class OptionNameOptionCoding : public AbstractOptionCoding {
 public:
  explicit OptionNameOptionCoding(const spl_conqueror::VariabilityModel &vm);
  ~OptionNameOptionCoding() override;
  spl_conqueror::BinaryOption *decode_binary_option(const std::string &str) const override;
  std::string encode_binary_options(const std::vector<spl_conqueror::BinaryOption *> &options) const override;

 public:
  OptionNameOptionCoding(const OptionNameOptionCoding &other) = delete;
  OptionNameOptionCoding(OptionNameOptionCoding &&other) noexcept = delete;
  OptionNameOptionCoding &operator=(const OptionNameOptionCoding &other) = delete;
  OptionNameOptionCoding &operator=(OptionNameOptionCoding &&other) noexcept = delete;
};

}

#endif //OPTION_NAME_OPTION_CODING_H
