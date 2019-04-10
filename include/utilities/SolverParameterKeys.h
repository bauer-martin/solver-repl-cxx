#ifndef SOLVER_PARAMETER_KEYS_H
#define SOLVER_PARAMETER_KEYS_H

namespace utilities {

struct SolverParameterKeys {
 public:
  static const char *random_seed;

  SolverParameterKeys() = delete;
  SolverParameterKeys(const SolverParameterKeys &other) = delete;
  SolverParameterKeys(SolverParameterKeys &&other) noexcept = delete;
  SolverParameterKeys &operator=(const SolverParameterKeys &other) = delete;
  SolverParameterKeys &operator=(SolverParameterKeys &&other) noexcept = delete;
};

}

#endif //SOLVER_PARAMETER_KEYS_H
