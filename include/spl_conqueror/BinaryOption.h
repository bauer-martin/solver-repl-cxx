#ifndef BINARY_OPTION_H
#define BINARY_OPTION_H

#include <boost/property_tree/ptree.hpp>
#include <string>
#include <vector>

namespace spl_conqueror {

class BinaryOption final {
 private:
  std::string _name;
  bool _is_optional;
  std::string *_parent_name;
  BinaryOption *_parent;
  std::vector<std::vector<std::string>> _implied_option_names;
  std::vector<std::vector<BinaryOption *>> _implied_options;
  std::vector<std::vector<std::string>> _excluded_option_names;
  std::vector<std::vector<BinaryOption *>> _excluded_options;
  BinaryOption(std::string name,
               bool is_optional,
               std::string *parent_name,
               std::vector<std::vector<std::string>> implied_option_names,
               std::vector<std::vector<std::string>> excluded_option_names);

 public:
  static BinaryOption *make_from_xml(const boost::property_tree::ptree &tree);
  static BinaryOption *make_root();
  ~BinaryOption();

  const std::string &get_name() const;
  bool is_optional() const;
  bool is_top_level() const;
  bool is_root() const;
  bool is_mandatory() const;

  // parent relationship
  bool has_parent() const;
  std::string *get_parent_name() const;
  void set_parent_name(std::string *option_name);
  BinaryOption *get_parent() const;
  void set_parent(BinaryOption *parent);
  bool is_child_of(const BinaryOption &option) const;
  bool has_ancestor(const BinaryOption &option) const;

  // implied, excluded and alternative options
  bool has_implied_options() const;
  const std::vector<std::vector<std::string>> &get_implied_option_names() const;
  const std::vector<std::vector<BinaryOption *>> &get_implied_options() const;
  void set_implied_options(const std::vector<std::vector<BinaryOption *>> &options);
  bool has_excluded_options() const;
  const std::vector<std::vector<std::string>> &get_excluded_option_names() const;
  const std::vector<std::vector<BinaryOption *>> &get_excluded_options() const;
  void set_excluded_options(const std::vector<std::vector<BinaryOption *>> &options);
  bool has_alternatives() const;
  bool is_alternative_group(const std::vector<BinaryOption *> &group) const;
  std::vector<BinaryOption *> collect_alternative_options() const;
  std::vector<std::vector<BinaryOption *>> get_non_alternative_excluded_options() const;

 public:
  BinaryOption(const BinaryOption &other) = delete;
  BinaryOption(BinaryOption &&other) noexcept = delete;
  BinaryOption &operator=(const BinaryOption &other) = delete;
  BinaryOption &operator=(BinaryOption &&other) noexcept = delete;
};

}

#endif //BINARY_OPTION_H
