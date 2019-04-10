#ifndef OR_TOOLS_SOLUTION_COLLECTOR_H
#define OR_TOOLS_SOLUTION_COLLECTOR_H

#include <atomic>

#include "ortools/sat/cp_model.h"
#include "ortools/sat/model.h"
#include "ortools/sat/sat_parameters.pb.h"
#include "ortools/util/time_limit.h"
#include "OrToolsConstraintSystemContext.h"

namespace or_tools {

class OrToolsSolutionCollector final {
 private:
  const OrToolsConstraintSystemContext &_context;
  const int _limit;
  std::vector<std::vector<spl_conqueror::BinaryOption *>> _solutions;
  operations_research::sat::Model *_model;
  std::atomic<bool> _solution_limit_reached;

 public:
  OrToolsSolutionCollector(const OrToolsConstraintSystemContext &context, uint seed);
  OrToolsSolutionCollector(const OrToolsConstraintSystemContext &context, uint seed, int limit);
  ~OrToolsSolutionCollector();
  operations_research::sat::Model *get_model() const;
  const std::vector<std::vector<spl_conqueror::BinaryOption *>> &get_solutions() const;

 public:
  OrToolsSolutionCollector(const OrToolsSolutionCollector &other) = delete;
  OrToolsSolutionCollector(OrToolsSolutionCollector &&other) noexcept = delete;
  OrToolsSolutionCollector &operator=(const OrToolsSolutionCollector &other) = delete;
  OrToolsSolutionCollector &operator=(OrToolsSolutionCollector &&other) noexcept = delete;
};

}

#endif //OR_TOOLS_SOLUTION_COLLECTOR_H
