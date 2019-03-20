#ifndef SAT_CHECKER_H
#define SAT_CHECKER_H

#include <vector>

#include "spl_conqueror/BinaryOption.h"
#include "spl_conqueror/VariabilityModel.h"

namespace spl_conqueror {

class SatChecker {
 protected:
  SatChecker();

 public:
  virtual ~SatChecker();
  virtual bool is_valid(const std::vector<BinaryOption *> &selected_options, bool is_partial_configuration) = 0;

 public:
  SatChecker(const SatChecker &other) = delete;
  SatChecker(SatChecker &&other) noexcept = delete;
  SatChecker &operator=(const SatChecker &other) = delete;
  SatChecker &operator=(SatChecker &&other) noexcept = delete;
};

}

#endif //SAT_CHECKER_H
