#include "spl_conqueror/VariabilityModel.h"

#include <boost/property_tree/ptree.hpp>
#include <stdexcept>

#include "utilities/Helpers.h"

#define ATTR_SET "<xmlattr>"

namespace spl_conqueror {

VariabilityModel *VariabilityModel::make_from_xml(const boost::property_tree::ptree &tree) {
  const boost::property_tree::ptree &vm_tree = tree.get_child("vm");

  const boost::property_tree::ptree &attributes = vm_tree.get_child(ATTR_SET);
  auto name = attributes.get<std::string>("name");
  helpers::trim(name);
  std::vector<BinaryOption *> binary_options;
  std::map<std::string, int> binary_options_index_by_name;
  std::vector<BinaryOption *> top_level_options;
  for (const boost::property_tree::ptree::value_type &v : vm_tree.get_child("binaryOptions")) {
    BinaryOption *option = BinaryOption::make_from_xml(v.second);
    if (option->is_top_level()) {
      top_level_options.push_back(option);
    }
    int index = binary_options.size();
    binary_options.push_back(option);
    binary_options_index_by_name[option->get_name()] = index;
  }
  std::vector<BinaryOption *> possible_root_options;
  for (auto &&option : top_level_options) {
    if (option->is_root()) {
      possible_root_options.push_back(option);
    }
  }
  std::string root_name;
  if (possible_root_options.size() == 1) {
    root_name = possible_root_options[0]->get_name();
  } else {
    BinaryOption *root = BinaryOption::make_root();
    root_name = root->get_name();
    int index = binary_options.size();
    binary_options.push_back(root);
    binary_options_index_by_name[root_name] = index;
  }
  std::vector<std::string> binary_constraints;
  for (const boost::property_tree::ptree::value_type &v : vm_tree.get_child("booleanConstraints")) {
    binary_constraints.push_back(v.second.data());
  }
  if (top_level_options.size() > 1) {
    for (auto &&option : top_level_options) {
      if (option->get_name() != root_name) {
        option->set_parent_name(new std::string(root_name));
      }
    }
  }
  return new VariabilityModel(name, binary_options, binary_constraints, binary_options_index_by_name, root_name);
}

VariabilityModel::VariabilityModel(std::string name,
                                   std::vector<BinaryOption *> binary_options,
                                   std::vector<std::string> binary_constraints,
                                   std::map<std::string, int> binary_options_index_by_name,
                                   std::string root_name)
    : _name(std::move(name)),
      _binary_options(std::move(binary_options)),
      _binary_constraints(std::move(binary_constraints)),
      _binary_options_index_by_name(std::move(binary_options_index_by_name)),
      _root_name(std::move(root_name)) {
  for (auto &&option : _binary_options) {
    if (option->has_parent()) {
      BinaryOption *parent = get_binary_option(*(option->get_parent_name()));
      option->set_parent(parent);
    }
    std::vector<std::vector<BinaryOption *>> implied_options;
    for (auto &&option_names : option->get_implied_option_names()) {
      std::vector<BinaryOption *> options;
      for (auto &&option_name : option_names) {
        BinaryOption *o = get_binary_option(option_name);
        options.push_back(o);
      }
      implied_options.push_back(options);
    }
    option->set_implied_options(implied_options);
    std::vector<std::vector<BinaryOption *>> excluded_options;
    for (auto &&option_names : option->get_excluded_option_names()) {
      std::vector<BinaryOption *> options;
      for (auto &&option_name : option_names) {
        BinaryOption *o = get_binary_option(option_name);
        options.push_back(o);
      }
      excluded_options.push_back(options);
    }
    option->set_excluded_options(excluded_options);
  }
}

VariabilityModel::~VariabilityModel() {
  for (auto &&option : _binary_options) {
    delete option;
  }
}

const std::string &VariabilityModel::get_name() const {
  return _name;
}

const std::vector<BinaryOption *> &VariabilityModel::get_binary_options() const {
  return _binary_options;
}

BinaryOption *VariabilityModel::get_binary_option(const std::string &option_name) const {
  auto search = _binary_options_index_by_name.find(option_name);
  if (search == _binary_options_index_by_name.end()) {
    throw std::runtime_error("'" + option_name + "' is not part of the variability model");
  } else {
    int index = search->second;
    return _binary_options[index];
  }
}

BinaryOption *VariabilityModel::get_root() const {
  return get_binary_option(_root_name);
}

const std::vector<std::string> &VariabilityModel::get_binary_constraints() const {
  return _binary_constraints;
}

}
