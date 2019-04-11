#include "option_coding/OptionNameOptionCoding.h"

#include <sstream>

namespace option_coding {

OptionNameOptionCoding::OptionNameOptionCoding(const spl_conqueror::VariabilityModel &vm) : OptionCoding(vm) {
}

OptionNameOptionCoding::~OptionNameOptionCoding() = default;

spl_conqueror::BinaryOption *OptionNameOptionCoding::decode_binary_option(const std::string &str) const {
  return _vm.get_binary_option(str);
}

std::vector<spl_conqueror::BinaryOption *> OptionNameOptionCoding::decode_binary_options(const std::string &str) const {
  std::istringstream ss(str);
  std::string option_name;
  std::vector<spl_conqueror::BinaryOption *> options;
  while (std::getline(ss, option_name, ',')) {
    options.push_back(decode_binary_option(option_name));
  }
  return options;
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

std::string OptionNameOptionCoding::encode_binary_options_vector(const std::vector<std::vector<spl_conqueror::BinaryOption *>> &configs) const {
  if (configs.empty()) {
    return "none";
  }
  std::stringstream ss;
  for (auto it = configs.cbegin(); it < configs.cend(); ++it) {
    std::vector<spl_conqueror::BinaryOption *> options = *it;
    ss << encode_binary_options(options);
    if (it < configs.end() - 1) {
      ss << ";";
    }
  }
  return ss.str();
}

std::string OptionNameOptionCoding::encode_binary_options_set(const std::set<std::vector<spl_conqueror::BinaryOption *>> &configs) const {
  if (configs.empty()) {
    return "none";
  }
  std::stringstream ss;
  for (auto &&options : configs) {
    ss << encode_binary_options(options);
    ss << ";";
  }
  std::string s = ss.str();
  s = s.substr(0, s.length() - 2);
  return s;
}

}
