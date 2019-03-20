#ifndef FIND_MINIMIZED_CONFIG_H
#define FIND_MINIMIZED_CONFIG_H

#include <string>

#include "utilities/GlobalContext.h"
#include "utilities/ShellCommand.h"

namespace commands {

class FindMinimizedConfig final : public utilities::ShellCommand {
 public:
  explicit FindMinimizedConfig(utilities::GlobalContext &global_context);
  std::string execute(const std::string &args_string) override;

 public:
  FindMinimizedConfig(const FindMinimizedConfig &other) = delete;
  FindMinimizedConfig(FindMinimizedConfig &&other) noexcept = delete;
  FindMinimizedConfig &operator=(const FindMinimizedConfig &other) = delete;
  FindMinimizedConfig &operator=(FindMinimizedConfig &&other) noexcept = delete;
};

}

#endif //FIND_MINIMIZED_CONFIG_H
