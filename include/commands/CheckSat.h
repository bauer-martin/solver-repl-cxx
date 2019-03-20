#ifndef CHECK_SAT_H
#define CHECK_SAT_H

#include <string>

#include "utilities/GlobalContext.h"
#include "utilities/ShellCommand.h"

namespace commands {

class CheckSat final : public utilities::ShellCommand {
 public:
  explicit CheckSat(utilities::GlobalContext &global_context);
  std::string execute(const std::string &args_string) override;

 public:
  CheckSat(const CheckSat &other) = delete;
  CheckSat(CheckSat &&other) noexcept = delete;
  CheckSat &operator=(const CheckSat &other) = delete;
  CheckSat &operator=(CheckSat &&other) noexcept = delete;
};

}

#endif //CHECK_SAT_H
