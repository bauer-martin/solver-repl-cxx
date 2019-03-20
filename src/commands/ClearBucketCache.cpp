#include "commands/ClearBucketCache.h"

namespace commands {

ClearBucketCache::ClearBucketCache(utilities::GlobalContext &global_context) : ShellCommand(global_context) {
}

std::string commands::ClearBucketCache::execute(const std::string &args_string) {
  _global_context.set_bucket_session(nullptr);
  return default_success_response();
}

}
