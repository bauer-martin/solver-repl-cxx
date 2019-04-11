#include "option_coding/OptionNameOptionCoding.h"

#include <sstream>

namespace option_coding {

OptionNameOptionCoding::OptionNameOptionCoding(const spl_conqueror::VariabilityModel &vm) : AbstractOptionCoding(vm) {
}

OptionNameOptionCoding::~OptionNameOptionCoding() = default;

spl_conqueror::BinaryOption *OptionNameOptionCoding::decode_binary_option(const std::string &str) const {
  return _vm.get_binary_option(str);
}

std::string OptionNameOptionCoding::encode_binary_options(const std::vector<spl_conqueror::BinaryOption *> &options) const {
  std::stringstream ss;
  for (auto it = options.cbegin(); it < options.cend(); ++it) {
    spl_conqueror::BinaryOption *option = *it;
    ss << option->get_name();
    if (it < options.end() - 1) {
      ss << ",";
    }
  }
  return ss.str();
}

}
