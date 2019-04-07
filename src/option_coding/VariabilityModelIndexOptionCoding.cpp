#include "option_coding/VariabilityModelIndexOptionCoding.h"

namespace option_coding {

static bool compare_binary_options(spl_conqueror::BinaryOption *option_1, spl_conqueror::BinaryOption *option_2) {
  return (option_1->get_name() < option_2->get_name());
}

VariabilityModelIndexOptionCoding::VariabilityModelIndexOptionCoding(const spl_conqueror::VariabilityModel &vm)
    : OptionCoding(vm), _encoding_substitutions(), _decoding_substitutions() {
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

std::vector<spl_conqueror::BinaryOption *> VariabilityModelIndexOptionCoding::decode_binary_options(const std::string &str) const {
  std::istringstream ss(str);
  std::string option_name;
  std::vector<spl_conqueror::BinaryOption *> options;
  while (std::getline(ss, option_name, ',')) {
    options.push_back(_vm.get_binary_option(_decoding_substitutions.at(option_name)));
  }
  return options;
}

std::string VariabilityModelIndexOptionCoding::encode_binary_options(const std::vector<spl_conqueror::BinaryOption *> &options) const {
  std::stringstream ss;
  for (auto it = options.begin(); it < options.end(); ++it) {
    spl_conqueror::BinaryOption *option = *it;
    ss << _encoding_substitutions.at(option->get_name());
    if (it < options.end() - 1) {
      ss << ",";
    }
  }
  return ss.str();
}

std::string VariabilityModelIndexOptionCoding::encode_binary_options_vector(const std::vector<std::vector<spl_conqueror::BinaryOption *>> &configs) const {
  if (configs.empty()) {
    return "none";
  }
  std::stringstream ss;
  for (auto it = configs.begin(); it < configs.end(); ++it) {
    std::vector<spl_conqueror::BinaryOption *> options = *it;
    ss << encode_binary_options(options);
    if (it < configs.end() - 1) {
      ss << ";";
    }
  }
  return ss.str();
}

std::string VariabilityModelIndexOptionCoding::encode_binary_options_set(const std::set<std::vector<spl_conqueror::BinaryOption *>> &configs) const {
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
