#ifndef SET_SEED_H
#define SET_SEED_H

#include <string>

#include "utilities/GlobalContext.h"
#include "utilities/ShellCommand.h"

namespace commands {

class SetSolverParameters final : public utilities::ShellCommand {
 public:
  explicit SetSolverParameters(utilities::GlobalContext &global_context);
  std::string execute(const std::string &args_string) override;

 public:
  SetSolverParameters(const SetSolverParameters &other) = delete;
  SetSolverParameters(SetSolverParameters &&other) noexcept = delete;
  SetSolverParameters &operator=(const SetSolverParameters &other) = delete;
  SetSolverParameters &operator=(SetSolverParameters &&other) noexcept = delete;
};

}

#endif //SET_SEED_H
