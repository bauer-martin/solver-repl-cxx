#include "utilities/ParsingUtils.h"

#include <sstream>

namespace utilities {

std::vector<spl_conqueror::BinaryOption *> decoded_binary_options(
    const std::string &str, const spl_conqueror::VariabilityModel &vm) {
  std::istringstream ss(str);
  std::string option_name;
  std::vector<spl_conqueror::BinaryOption *> options;
  while (std::getline(ss, option_name, ',')) {
    options.push_back(vm.get_binary_option(option_name));
  }
  return options;
}

std::string encoded_binary_options(const std::vector<spl_conqueror::BinaryOption *> &options) {
  std::stringstream ss;
  for (auto it = options.begin(); it < options.end(); ++it) {
    spl_conqueror::BinaryOption *option = *it;
    ss << option->get_name();
    if (it < options.end() - 1) {
      ss << ",";
    }
  }
  return ss.str();
}

std::string encoded_binary_options_vector(const std::vector<std::vector<spl_conqueror::BinaryOption *>> &configs) {
  if (configs.empty()) {
    return "none";
  }
  std::stringstream ss;
  for (auto it = configs.begin(); it < configs.end(); ++it) {
    std::vector<spl_conqueror::BinaryOption *> options = *it;
    ss << encoded_binary_options(options);
    if (it < configs.end() - 1) {
      ss << ";";
    }
  }
  return ss.str();
}

std::string encoded_binary_options_set(const std::set<std::vector<spl_conqueror::BinaryOption *>> &configs) {
  if (configs.empty()) {
    return "none";
  }
  std::stringstream ss;
  for (auto &&options : configs) {
    ss << encoded_binary_options(options);
    ss << ";";
  }
  std::string s = ss.str();
  s = s.substr(0, s.length() - 2);
  return s;
}

}
