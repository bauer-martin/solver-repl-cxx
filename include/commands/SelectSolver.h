#ifndef SELECT_SOLVER_H
#define SELECT_SOLVER_H

#include <map>
#include <string>

#include "spl_conqueror/SolverFacade.h"
#include "spl_conqueror/VariabilityModel.h"
#include "utilities/GlobalContext.h"
#include "utilities/ShellCommand.h"

namespace commands {

typedef spl_conqueror::SolverFacade *(*SolverFacadeInit)(const spl_conqueror::VariabilityModel &);

class SelectSolver final : public utilities::ShellCommand {
 private:
  std::map<std::string, SolverFacadeInit> _solver_types;

 public:
  explicit SelectSolver(utilities::GlobalContext &global_context);
  void register_solver(const std::string &solver_name, SolverFacadeInit init);
  std::string execute(const std::string &args_string) override;

 public:
  SelectSolver(const SelectSolver &other) = delete;
  SelectSolver(SelectSolver &&other) noexcept = delete;
  SelectSolver &operator=(const SelectSolver &other) = delete;
  SelectSolver &operator=(SelectSolver &&other) noexcept = delete;
};

}

#endif //SELECT_SOLVER_H
