#ifndef CLEAR_BUCKET_CACHE_H
#define CLEAR_BUCKET_CACHE_H

#include <string>

#include "utilities/GlobalContext.h"
#include "utilities/ShellCommand.h"

namespace commands {

class ClearBucketCache final : public utilities::ShellCommand {
 public:
  explicit ClearBucketCache(utilities::GlobalContext &global_context);
  std::string execute(const std::string &args_string) override;

 public:
  ClearBucketCache(const ClearBucketCache &other) = delete;
  ClearBucketCache(ClearBucketCache &&other) noexcept = delete;
  ClearBucketCache &operator=(const ClearBucketCache &other) = delete;
  ClearBucketCache &operator=(ClearBucketCache &&other) noexcept = delete;
};

}

#endif //CLEAR_BUCKET_CACHE_H
