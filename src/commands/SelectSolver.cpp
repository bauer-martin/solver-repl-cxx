#include "commands/SelectSolver.h"

namespace commands {

SelectSolver::SelectSolver(utilities::GlobalContext &global_context) : ShellCommand(global_context),
                                                                       _solver_types() {
}

void SelectSolver::register_solver(const std::string &solver_name, SolverFacadeInit init) {
  _solver_types.emplace(solver_name, init);
}

std::string SelectSolver::execute(const std::string &args_string) {
  auto search = _solver_types.find(args_string);
  if (search == _solver_types.end()) {
    return error("unknown solver '" + args_string + "'");
  }
  SolverFacadeInit init = search->second;
  spl_conqueror::VariabilityModel &vm = _global_context.get_variability_model();
  spl_conqueror::SolverFacade *facade = init(vm);
  _global_context.set_solver_facade(facade);
  return default_success_response();
}

}
