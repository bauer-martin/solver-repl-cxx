#ifndef OPTI_MATH_SAT_CONSTRAINT_SYSTEM_CONTEXT_H
#define OPTI_MATH_SAT_CONSTRAINT_SYSTEM_CONTEXT_H

#include <map>
#include <set>
#include <vector>

#include "optimathsat.h"
#include "spl_conqueror/BinaryOption.h"
#include "spl_conqueror/VariabilityModel.h"

namespace opti_math_sat {

class OptiMathSatConstraintSystemContext final {
 private:
  const spl_conqueror::VariabilityModel &_vm;
  const msat_config _config;
  const msat_env _environment;
  std::vector<msat_term> _variables;
  std::map<std::string, int> _option_name_to_variable_index;
  msat_term _feature_model;
  OptiMathSatConstraintSystemContext(const spl_conqueror::VariabilityModel &vm,
                                     msat_config &config,
                                     msat_env &environment,
                                     std::vector<msat_term> variables,
                                     msat_term &feature_model);
  void add_constraint(const msat_term &term);
  void create_variables();
  void process_binary_options();
  void add_variable_constraints(const spl_conqueror::BinaryOption &option);
  void process_alternative_options(std::set<std::string> &processed_alternatives,
                                   const spl_conqueror::BinaryOption &option);
  void process_excluded_options_as_cross_tree_constraints(const spl_conqueror::BinaryOption &option);
  void process_implied_options(const spl_conqueror::BinaryOption &option);
  void process_binary_constraints();

 public:
  static OptiMathSatConstraintSystemContext *make_from(const spl_conqueror::VariabilityModel &vm);
  ~OptiMathSatConstraintSystemContext();
  const msat_term &option_to_var(const spl_conqueror::BinaryOption &option) const;
  const msat_env &get_environment() const;
  const spl_conqueror::VariabilityModel &get_variability_model() const;
  void mark_checkpoint();
  void reset_to_last_checkpoint();

 public:
  OptiMathSatConstraintSystemContext(const OptiMathSatConstraintSystemContext &other) = delete;
  OptiMathSatConstraintSystemContext(OptiMathSatConstraintSystemContext &&other) noexcept = delete;
  OptiMathSatConstraintSystemContext &operator=(const OptiMathSatConstraintSystemContext &other) = delete;
  OptiMathSatConstraintSystemContext &operator=(OptiMathSatConstraintSystemContext &&other) noexcept = delete;
};

}

#endif //OPTI_MATH_SAT_CONSTRAINT_SYSTEM_CONTEXT_H
