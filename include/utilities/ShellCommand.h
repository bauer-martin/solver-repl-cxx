#ifndef SHELL_COMMAND_H
#define SHELL_COMMAND_H

#include <string>

#include "utilities/GlobalContext.h"

namespace utilities {

class ShellCommand {
 protected:
  utilities::GlobalContext &_global_context;
  explicit ShellCommand(utilities::GlobalContext &global_context) : _global_context(global_context) {}

 protected:
  static std::string default_success_response();
  static std::string error(const std::string &message);

 public:
  virtual ~ShellCommand();
  virtual std::string execute(const std::string &args_string) = 0;

 public:
  ShellCommand(const ShellCommand &other) = delete;
  ShellCommand(ShellCommand &&other) noexcept = delete;
  ShellCommand &operator=(const ShellCommand &other) = delete;
  ShellCommand &operator=(ShellCommand &&other) noexcept = delete;
};

}

#endif //SHELL_COMMAND_H
