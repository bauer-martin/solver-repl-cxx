#ifndef OR_TOOLS_CONSTRAINT_SYSTEM_CONTEXT_H
#define OR_TOOLS_CONSTRAINT_SYSTEM_CONTEXT_H

#include <map>
#include <set>
#include <vector>

#include "ortools/sat/cp_model.h"
#include "spl_conqueror/BinaryOption.h"
#include "spl_conqueror/VariabilityModel.h"

namespace ort = operations_research::sat;

namespace or_tools {

class OrToolsConstraintSystemContext final {
 private:
  const spl_conqueror::VariabilityModel &_vm;
  ort::CpModelBuilder _model;
  std::vector<ort::BoolVar> _variables;
  std::map<std::string, int> _option_name_to_variable_index;
  OrToolsConstraintSystemContext(const spl_conqueror::VariabilityModel &vm,
                                 std::vector<ort::BoolVar> variables);
  void create_variables();
  void process_binary_options();
  void add_variable_constraints(const spl_conqueror::BinaryOption &option);
  void process_alternative_options(std::set<std::string> &processed_alternatives,
                                   const spl_conqueror::BinaryOption &option);
  void process_excluded_options_as_cross_tree_constraints(const spl_conqueror::BinaryOption &option);
  void process_implied_options(const spl_conqueror::BinaryOption &option);
  void process_binary_constraints();

 public:
  static OrToolsConstraintSystemContext *make_from(const spl_conqueror::VariabilityModel &vm);
  ~OrToolsConstraintSystemContext();
  const ort::BoolVar &option_to_var(const spl_conqueror::BinaryOption &option) const;
  ort::CpModelBuilder &get_model();
  const spl_conqueror::VariabilityModel &get_variability_model() const;

 public:
  OrToolsConstraintSystemContext(const OrToolsConstraintSystemContext &other) = delete;
  OrToolsConstraintSystemContext(OrToolsConstraintSystemContext &&other) noexcept = delete;
  OrToolsConstraintSystemContext &operator=(const OrToolsConstraintSystemContext &other) = delete;
  OrToolsConstraintSystemContext &operator=(OrToolsConstraintSystemContext &&other) noexcept = delete;
};

}

#endif //OR_TOOLS_CONSTRAINT_SYSTEM_CONTEXT_H
