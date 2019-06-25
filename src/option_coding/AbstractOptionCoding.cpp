#include "option_coding/AbstractOptionCoding.h"

#include <sstream>

namespace option_coding {

AbstractOptionCoding::AbstractOptionCoding(const spl_conqueror::VariabilityModel &vm) : OptionCoding(vm) {
}

AbstractOptionCoding::~AbstractOptionCoding() = default;

std::vector<spl_conqueror::BinaryOption *> AbstractOptionCoding::decode_binary_options(const std::string &str) const {
  std::istringstream ss(str);
  std::string option_name;
  std::vector<spl_conqueror::BinaryOption *> options;
  while (std::getline(ss, option_name, ',')) {
    options.push_back(decode_binary_option(option_name));
  }
  return options;
}

std::string AbstractOptionCoding::encode_binary_options_vector(const std::vector<std::vector<spl_conqueror::BinaryOption *>> &configs) const {
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

std::string AbstractOptionCoding::encode_binary_options_set(const std::set<std::vector<spl_conqueror::BinaryOption *>> &configs) const {
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
