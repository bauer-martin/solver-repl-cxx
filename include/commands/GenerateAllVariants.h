#ifndef GENERATE_ALL_VARIANTS_H
#define GENERATE_ALL_VARIANTS_H

#include <string>

#include "utilities/GlobalContext.h"
#include "utilities/ShellCommand.h"

namespace commands {

class GenerateAllVariants final : public utilities::ShellCommand {
 public:
  explicit GenerateAllVariants(utilities::GlobalContext &global_context);
  std::string execute(const std::string &args_string) override;

 public:
  GenerateAllVariants(const GenerateAllVariants &other) = delete;
  GenerateAllVariants(GenerateAllVariants &&other) noexcept = delete;
  GenerateAllVariants &operator=(const GenerateAllVariants &other) = delete;
  GenerateAllVariants &operator=(GenerateAllVariants &&other) noexcept = delete;
};

}

#endif //GENERATE_ALL_VARIANTS_H
