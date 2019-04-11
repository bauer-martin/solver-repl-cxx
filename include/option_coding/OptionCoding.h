#ifndef OPTION_CODING_H
#define OPTION_CODING_H

#include <set>
#include <string>
#include <vector>

#include "spl_conqueror/BinaryOption.h"
#include "spl_conqueror/VariabilityModel.h"

namespace option_coding {

class OptionCoding {
 protected:
  const spl_conqueror::VariabilityModel &_vm;
  explicit OptionCoding(const spl_conqueror::VariabilityModel &vm);

 public:
  virtual ~OptionCoding();
  virtual spl_conqueror::BinaryOption *decode_binary_option(const std::string &str) const = 0;
  virtual std::vector<spl_conqueror::BinaryOption *> decode_binary_options(const std::string &str) const = 0;
  virtual std::string encode_binary_options(const std::vector<spl_conqueror::BinaryOption *> &options) const = 0;
  virtual std::string encode_binary_options_vector(
      const std::vector<std::vector<spl_conqueror::BinaryOption *>> &configs) const = 0;
  virtual std::string encode_binary_options_set(
      const std::set<std::vector<spl_conqueror::BinaryOption *>> &configs) const = 0;
};

}

#endif //OPTION_CODING_H
