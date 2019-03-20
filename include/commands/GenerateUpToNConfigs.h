#ifndef GENERATE_UP_TO_N_CONFIGS_H
#define GENERATE_UP_TO_N_CONFIGS_H

#include <string>

#include "utilities/GlobalContext.h"
#include "utilities/ShellCommand.h"

namespace commands {

class GenerateUpToNConfigs final : public utilities::ShellCommand {
 public:
  explicit GenerateUpToNConfigs(utilities::GlobalContext &global_context);
  std::string execute(const std::string &args_string) override;

 public:
  GenerateUpToNConfigs(const GenerateUpToNConfigs &other) = delete;
  GenerateUpToNConfigs(GenerateUpToNConfigs &&other) noexcept = delete;
  GenerateUpToNConfigs &operator=(const GenerateUpToNConfigs &other) = delete;
  GenerateUpToNConfigs &operator=(GenerateUpToNConfigs &&other) noexcept = delete;
};

}

#endif //GENERATE_UP_TO_N_CONFIGS_H
