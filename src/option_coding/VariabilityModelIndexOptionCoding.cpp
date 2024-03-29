#include "option_coding/VariabilityModelIndexOptionCoding.h"

namespace option_coding {

static bool compare_binary_options(spl_conqueror::BinaryOption *option_1, spl_conqueror::BinaryOption *option_2) {
  const std::string &str_1 = option_1->get_name();
  const std::string &str_2 = option_2->get_name();
  auto result = mismatch(str_1.cbegin(), str_1.cend(), str_2.cbegin(),
                         [](const unsigned char lhs, const unsigned char rhs) {
                           return tolower(lhs) == tolower(rhs);
                         });
  return result.second != str_2.cend()
      && (result.first == str_1.cend() || tolower(*result.first) < tolower(*result.second));
}

VariabilityModelIndexOptionCoding::VariabilityModelIndexOptionCoding(const spl_conqueror::VariabilityModel &vm)
    : AbstractOptionCoding(vm), _encoding_substitutions(), _decoding_substitutions() {
  std::vector<spl_conqueror::BinaryOption *> options
      = std::vector<spl_conqueror::BinaryOption *>(_vm.get_binary_options());
  std::sort(options.begin(), options.end(), compare_binary_options);
  for (int i = 0; i < options.size(); i++) {
    std::string value = options[i]->get_name();
    std::string substitution = std::to_string(i);
    _encoding_substitutions[value] = substitution;
    _decoding_substitutions[substitution] = value;
  }
}

VariabilityModelIndexOptionCoding::~VariabilityModelIndexOptionCoding() = default;

spl_conqueror::BinaryOption *VariabilityModelIndexOptionCoding::decode_binary_option(const std::string &str) const {
  return _vm.get_binary_option(_decoding_substitutions.at(str));
}

std::string VariabilityModelIndexOptionCoding::encode_binary_options(const std::vector<spl_conqueror::BinaryOption *> &options) const {
  std::stringstream ss;
  for (auto it = options.cbegin(); it < options.cend(); ++it) {
    spl_conqueror::BinaryOption *option = *it;
    ss << _encoding_substitutions.at(option->get_name());
    if (it < options.cend() - 1) {
      ss << ",";
    }
  }
  return ss.str();
}

}
