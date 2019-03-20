#ifndef VARIABILITY_MODEL_H
#define VARIABILITY_MODEL_H

#include <boost/property_tree/ptree.hpp>
#include <map>
#include <string>
#include <vector>

#include "spl_conqueror/BinaryOption.h"

namespace spl_conqueror {

class VariabilityModel final {
 private:
  std::string _name;
  std::vector<BinaryOption *> _binary_options;
  std::vector<std::string> _binary_constraints;
  std::map<std::string, int> _binary_options_index_by_name;
  std::string _root_name;
  VariabilityModel(std::string name,
                   std::vector<BinaryOption *> binary_options,
                   std::vector<std::string> binary_constraints,
                   std::map<std::string, int> binary_options_index_by_name,
                   std::string root_name);

 public:
  static VariabilityModel *make_from_xml(const boost::property_tree::ptree &tree);
  ~VariabilityModel();

  const std::string &get_name() const;
  const std::vector<BinaryOption *> &get_binary_options() const;
  BinaryOption *get_binary_option(const std::string &option_name) const;
  BinaryOption *get_root() const;
  const std::vector<std::string> &get_binary_constraints() const;

 public:
  VariabilityModel(const VariabilityModel &other) = delete;
  VariabilityModel(VariabilityModel &&other) noexcept = delete;
  VariabilityModel &operator=(const VariabilityModel &other) = delete;
  VariabilityModel &operator=(VariabilityModel &&other) noexcept = delete;
};

}

#endif //VARIABILITY_MODEL_H
