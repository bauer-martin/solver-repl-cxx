#ifndef GENERATE_CONFIGS_FROM_BUCKET_H
#define GENERATE_CONFIGS_FROM_BUCKET_H

#include <string>

#include "utilities/GlobalContext.h"
#include "utilities/ShellCommand.h"

namespace commands {

class GenerateConfigFromBucket final : public utilities::ShellCommand {
 public:
  explicit GenerateConfigFromBucket(utilities::GlobalContext &global_context);
  std::string execute(const std::string &args_string) override;

 public:
  GenerateConfigFromBucket(const GenerateConfigFromBucket &other) = delete;
  GenerateConfigFromBucket(GenerateConfigFromBucket &&other) noexcept = delete;
  GenerateConfigFromBucket &operator=(const GenerateConfigFromBucket &other) = delete;
  GenerateConfigFromBucket &operator=(GenerateConfigFromBucket &&other) noexcept = delete;
};

}

#endif //GENERATE_CONFIGS_FROM_BUCKET_H
