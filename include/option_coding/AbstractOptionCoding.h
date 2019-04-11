#ifndef ABSTRACT_OPTION_CODING_H
#define ABSTRACT_OPTION_CODING_H

#include "option_coding/OptionCoding.h"

namespace option_coding {

class AbstractOptionCoding : public OptionCoding {
 protected:
  explicit AbstractOptionCoding(const spl_conqueror::VariabilityModel &vm);

 public:
  ~AbstractOptionCoding() override;
  std::vector<spl_conqueror::BinaryOption *> decode_binary_options(const std::string &str) const override;
  std::string encode_binary_options_vector(const std::vector<std::vector<spl_conqueror::BinaryOption *>> &configs) const override;
  std::string encode_binary_options_set(const std::set<std::vector<spl_conqueror::BinaryOption *>> &configs) const override;

 public:
  AbstractOptionCoding(const AbstractOptionCoding &other) = delete;
  AbstractOptionCoding(AbstractOptionCoding &&other) noexcept = delete;
  AbstractOptionCoding &operator=(const AbstractOptionCoding &other) = delete;
  AbstractOptionCoding &operator=(AbstractOptionCoding &&other) noexcept = delete;
};

}

#endif //ABSTRACT_OPTION_CODING_H
