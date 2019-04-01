#ifndef OR_TOOLS_SAT_CHECKER_H
#define OR_TOOLS_SAT_CHECKER_H

#include "spl_conqueror/SatChecker.h"
#include "spl_conqueror/VariabilityModel.h"

namespace or_tools {

class OrToolsSatChecker final : public spl_conqueror::SatChecker {
 private:
  const spl_conqueror::VariabilityModel &_vm;

 public:
  explicit OrToolsSatChecker(const spl_conqueror::VariabilityModel &vm);
  bool is_valid(const std::vector<spl_conqueror::BinaryOption *> &selected_options,
                bool is_partial_configuration) override;

 public:
  OrToolsSatChecker(const OrToolsSatChecker &other) = delete;
  OrToolsSatChecker(OrToolsSatChecker &&other) noexcept = delete;
  OrToolsSatChecker &operator=(const OrToolsSatChecker &other) = delete;
  OrToolsSatChecker &operator=(OrToolsSatChecker &&other) noexcept = delete;
};

}

#endif //OR_TOOLS_SAT_CHECKER_H
