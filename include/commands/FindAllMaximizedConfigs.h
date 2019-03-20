#ifndef FIND_ALL_MAXIMIZED_CONFIGS_H
#define FIND_ALL_MAXIMIZED_CONFIGS_H

#include <string>

#include "utilities/GlobalContext.h"
#include "utilities/ShellCommand.h"

namespace commands {

class FindAllMaximizedConfigs final : public utilities::ShellCommand {
 public:
  explicit FindAllMaximizedConfigs(utilities::GlobalContext &global_context);
  std::string execute(const std::string &args_string) override;

 public:
  FindAllMaximizedConfigs(const FindAllMaximizedConfigs &other) = delete;
  FindAllMaximizedConfigs(FindAllMaximizedConfigs &&other) noexcept = delete;
  FindAllMaximizedConfigs &operator=(const FindAllMaximizedConfigs &other) = delete;
  FindAllMaximizedConfigs &operator=(FindAllMaximizedConfigs &&other) noexcept = delete;
};

}

#endif //FIND_ALL_MAXIMIZED_CONFIGS_H
