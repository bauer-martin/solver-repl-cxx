#ifndef GENERATE_CONFIG_WITHOUT_OPTION_H
#define GENERATE_CONFIG_WITHOUT_OPTION_H

#include <string>

#include "utilities/GlobalContext.h"
#include "utilities/ShellCommand.h"

namespace commands {

class GenerateConfigWithoutOption final : public utilities::ShellCommand {
 public:
  explicit GenerateConfigWithoutOption(utilities::GlobalContext &global_context);
  std::string execute(const std::string &args_string) override;

 public:
  GenerateConfigWithoutOption(const GenerateConfigWithoutOption &other) = delete;
  GenerateConfigWithoutOption(GenerateConfigWithoutOption &&other) noexcept = delete;
  GenerateConfigWithoutOption &operator=(const GenerateConfigWithoutOption &other) = delete;
  GenerateConfigWithoutOption &operator=(GenerateConfigWithoutOption &&other) noexcept = delete;
};

}

#endif //GENERATE_CONFIG_WITHOUT_OPTION_H
