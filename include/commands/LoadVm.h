#ifndef LOAD_VM_H
#define LOAD_VM_H

#include <string>

#include "utilities/GlobalContext.h"
#include "utilities/ShellCommand.h"

namespace commands {

class LoadVm final : public utilities::ShellCommand {
 public:
  explicit LoadVm(utilities::GlobalContext &global_context);
  std::string execute(const std::string &args_string) override;

 public:
  LoadVm(const LoadVm &other) = delete;
  LoadVm(LoadVm &&other) noexcept = delete;
  LoadVm &operator=(const LoadVm &other) = delete;
  LoadVm &operator=(LoadVm &&other) noexcept = delete;
};

}

#endif //LOAD_VM_H
