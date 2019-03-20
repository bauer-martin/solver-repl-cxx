#include "spl_conqueror/BinaryOption.h"

#include <boost/algorithm/string.hpp>
#include <boost/property_tree/ptree.hpp>

#include "utilities/Helpers.h"

namespace pt = boost::property_tree;

namespace spl_conqueror {

BinaryOption *BinaryOption::make_from_xml(const boost::property_tree::ptree &tree) {
  auto name = tree.get<std::string>("name");
  helpers::trim(name);
  bool is_optional = tree.get<std::string>("optional") == "True";
  auto parent_name = tree.get<std::string>("parent");
  helpers::trim(parent_name);
  std::vector<std::vector<std::string>> implied_option_names = {};
  for (const pt::ptree::value_type &v : tree.get_child("impliedOptions")) {
    std::string names = v.second.data();
    helpers::trim(name);
    std::vector<std::string> names_list;
    // TODO trim names
    boost::split(names_list, names, boost::is_any_of("|"));
    for (auto &&option_name : names_list) {
      helpers::trim(option_name);
    }
    implied_option_names.push_back(names_list);
  }
  std::vector<std::vector<std::string>> excluded_option_names = {};
  for (const pt::ptree::value_type &v : tree.get_child("excludedOptions")) {
    std::string names = v.second.data();
    helpers::trim(names);
    std::vector<std::string> names_list;
    // TODO trim names
    boost::split(names_list, names, boost::is_any_of("|"));
    for (auto &&option_name : names_list) {
      helpers::trim(option_name);
    }
    excluded_option_names.push_back(names_list);
  }
  return new BinaryOption(
      name,
      is_optional,
      parent_name.empty() ? nullptr : new std::string(parent_name),
      implied_option_names,
      excluded_option_names
  );
}

BinaryOption *BinaryOption::make_root() {
  return new BinaryOption("root", false, nullptr, {}, {});
}

BinaryOption::BinaryOption(std::string name,
                           bool is_optional,
                           std::string *parent_name,
                           std::vector<std::vector<std::string>> implied_option_names,
                           std::vector<std::vector<std::string>> excluded_option_names)
    : _name(std::move(name)),
      _is_optional(is_optional),
      _parent_name(parent_name),
      _parent(nullptr),
      _implied_option_names(std::move(implied_option_names)),
      _implied_options(),
      _excluded_option_names(std::move(excluded_option_names)),
      _excluded_options() {
}

BinaryOption::~BinaryOption() {
  delete _parent_name;
}

const std::string &BinaryOption::get_name() const {
  return _name;
}

bool BinaryOption::is_optional() const {
  return _is_optional;
}

bool BinaryOption::is_top_level() const {
  return _parent_name == nullptr;
}

bool BinaryOption::is_root() const {
  return is_top_level() && is_mandatory();
}

bool BinaryOption::is_mandatory() const {
  return !_is_optional;
}

// parent relationship

bool BinaryOption::has_parent() const {
  return _parent_name != nullptr;
}

std::string *BinaryOption::get_parent_name() const {
  return _parent_name;
}

void BinaryOption::set_parent_name(std::string *option_name) {
  _parent_name = option_name;
}

BinaryOption *BinaryOption::get_parent() const {
  return _parent;
}

void BinaryOption::set_parent(BinaryOption *option) {
  _parent = option;
}

bool BinaryOption::is_child_of(const BinaryOption &option) const {
  if (has_parent()) {
    return *_parent_name == option.get_name();
  } else {
    return false;
  }
}

bool BinaryOption::has_ancestor(const BinaryOption &option) const {
  if (has_parent()) {
    return is_child_of(option) || _parent->has_ancestor(option);
  } else {
    return false;
  }
}

// implied, excluded and alternative options

bool BinaryOption::has_implied_options() const {
  return !_implied_option_names.empty();
}

const std::vector<std::vector<std::string>> &BinaryOption::get_implied_option_names() const {
  return _implied_option_names;
}

const std::vector<std::vector<BinaryOption *>> &BinaryOption::get_implied_options() const {
  return _implied_options;
}

void BinaryOption::set_implied_options(const std::vector<std::vector<BinaryOption *>> &options) {
  _implied_options = options;
}

bool BinaryOption::has_excluded_options() const {
  return !_excluded_option_names.empty();
}

const std::vector<std::vector<std::string>> &BinaryOption::get_excluded_option_names() const {
  return _excluded_option_names;
}

const std::vector<std::vector<BinaryOption *>> &BinaryOption::get_excluded_options() const {
  return _excluded_options;
}

void BinaryOption::set_excluded_options(const std::vector<std::vector<BinaryOption *>> &options) {
  _excluded_options = options;
}

bool BinaryOption::has_alternatives() const {
  for (auto &&excluded_option : _excluded_options) {
    if (is_alternative_group(excluded_option)) {
      return true;
    }
  }
  return false;
}

bool BinaryOption::is_alternative_group(const std::vector<BinaryOption *> &group) const {
  if (_is_optional) {
    return false;
  }
  for (auto &&option : group) {
    if (option->_name != _name) {
      return false;
    }
  }
  return true;
}

std::vector<BinaryOption *> BinaryOption::collect_alternative_options() const {
  std::vector<BinaryOption *> result;
  if (is_optional()) {
    return result;
  }
  for (auto &&group : _excluded_options) {
    if (group.size() == 1) {
      BinaryOption *option = group[0];
      if (option->has_parent() && *(option->_parent_name) == _parent->_name && option->is_mandatory()) {
        result.push_back(option);
      }
    }
  }
  return result;
}

std::vector<std::vector<BinaryOption *>> BinaryOption::get_non_alternative_excluded_options() const {
  std::vector<std::vector<BinaryOption *>> result;
  for (auto &&group : _excluded_options) {
    if (group.size() == 1) {
      BinaryOption *option = group[0];
      if (option->has_parent() && *(option->_parent_name) == _parent->_name) {
        if (is_optional() && option->is_optional()) {
          result.push_back(group);
        }
      } else {
        result.push_back(group);
      }
    }
  }
  return result;
}

}
