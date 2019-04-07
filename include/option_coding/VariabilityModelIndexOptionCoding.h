#ifndef INDEX_BASED_OPTION_CODING_H
#define INDEX_BASED_OPTION_CODING_H

#include <map>

#include "option_coding/OptionCoding.h"

namespace option_coding {

class VariabilityModelIndexOptionCoding : public OptionCoding {
 private:
   std::map<std::string, std::string> _encoding_substitutions;
   std::map<std::string, std::string> _decoding_substitutions;

 public:
  explicit VariabilityModelIndexOptionCoding(const spl_conqueror::VariabilityModel &vm);
  ~VariabilityModelIndexOptionCoding() override;
  std::vector<spl_conqueror::BinaryOption *> decode_binary_options(const std::string &str) const override;
  std::string encode_binary_options(const std::vector<spl_conqueror::BinaryOption *> &options) const override;
  std::string encode_binary_options_vector(
      const std::vector<std::vector<spl_conqueror::BinaryOption *>> &configs) const override;
  std::string encode_binary_options_set(
      const std::set<std::vector<spl_conqueror::BinaryOption *>> &configs) const override;

 public:
  VariabilityModelIndexOptionCoding(const VariabilityModelIndexOptionCoding &other) = delete;
  VariabilityModelIndexOptionCoding(VariabilityModelIndexOptionCoding &&other) noexcept = delete;
  VariabilityModelIndexOptionCoding &operator=(const VariabilityModelIndexOptionCoding &other) = delete;
  VariabilityModelIndexOptionCoding &operator=(VariabilityModelIndexOptionCoding &&other) noexcept = delete;
};

}

#endif //INDEX_BASED_OPTION_CODING_H
