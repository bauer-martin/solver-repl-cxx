#ifndef BUCKET_SESSION_H
#define BUCKET_SESSION_H

#include <vector>

#include "spl_conqueror/BinaryOption.h"

namespace spl_conqueror {

class BucketSession {
 protected:
  BucketSession();

 public:
  virtual ~BucketSession();
  virtual std::vector<BinaryOption *> *generate_config(
      int selected_options_count,
      const std::vector<std::vector<BinaryOption *>> &feature_ranking) = 0;

 public:
  BucketSession(const BucketSession &other) = delete;
  BucketSession(BucketSession &&other) noexcept = delete;
  BucketSession &operator=(const BucketSession &other) = delete;
  BucketSession &operator=(BucketSession &&other) noexcept = delete;
};

}

#endif //BUCKET_SESSION_H
