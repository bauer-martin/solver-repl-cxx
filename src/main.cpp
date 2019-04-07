#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "commands/CheckSat.h"
#include "commands/ClearBucketCache.h"
#include "commands/FindAllMaximizedConfigs.h"
#include "commands/FindMinimizedConfig.h"
#include "commands/GenerateAllVariants.h"
#include "commands/GenerateConfigFromBucket.h"
#include "commands/GenerateConfigWithoutOption.h"
#include "commands/GenerateUpToNConfigs.h"
#include "commands/LoadVm.h"
#include "commands/SelectOptionCoding.h"
#include "commands/SelectSolver.h"
#include "option_coding/OptionNameOptionCoding.h"
#include "option_coding/VariabilityModelIndexOptionCoding.h"
#ifdef USE_OPTIMATHSAT
#include "opti_math_sat/OptiMathSatSolverFactory.h"
#endif
#ifdef USE_OR_TOOLS
#include "or_tools/OrToolsSolverFactory.h"
#endif
#include "spl_conqueror/BinaryOption.h"
#include "utilities/Shell.h"
#include "utilities/GlobalContext.h"

static int run_shell(std::istream &input) {
  utilities::Shell shell(input);
  utilities::GlobalContext context;
  shell.register_command("load-vm", new commands::LoadVm(context));
  auto *select_solver_command = new commands::SelectSolver(context);
#ifdef USE_OPTIMATHSAT
  select_solver_command->register_solver(
      "opti-math-sat",
      [](const spl_conqueror::VariabilityModel &vm) -> spl_conqueror::SolverFactory * {
        return new opti_math_sat::OptiMathSatSolverFactory(vm);
      });
#endif
#ifdef USE_OR_TOOLS
  select_solver_command->register_solver(
      "or-tools",
      [](const spl_conqueror::VariabilityModel &vm) -> spl_conqueror::SolverFactory * {
        return new or_tools::OrToolsSolverFactory(vm);
      });
#endif
  shell.register_command("select-solver", select_solver_command);
  auto *select_option_coding_command = new commands::SelectOptionCoding(context);
  select_option_coding_command->register_option_coding(
      "option-name",
      [](const spl_conqueror::VariabilityModel &vm) -> option_coding::OptionCoding * {
        return new option_coding::OptionNameOptionCoding(vm);
      });
  select_option_coding_command->register_option_coding(
      "variability-model-index",
      [](const spl_conqueror::VariabilityModel &vm) -> option_coding::OptionCoding * {
        return new option_coding::VariabilityModelIndexOptionCoding(vm);
      });
  shell.register_command("select-option-coding", select_option_coding_command);
  shell.register_command("check-sat", new commands::CheckSat(context));
  shell.register_command("find-minimized-config", new commands::FindMinimizedConfig(context));
  shell.register_command("find-all-maximized-configs", new commands::FindAllMaximizedConfigs(context));
  shell.register_command("generate-up-to", new commands::GenerateUpToNConfigs(context));
  shell.register_command("generate-config-without-option", new commands::GenerateConfigWithoutOption(context));
  shell.register_command("generate-all-variants", new commands::GenerateAllVariants(context));
  shell.register_command("generate-config-from-bucket", new commands::GenerateConfigFromBucket(context));
  shell.register_command("clear-bucket-cache", new commands::ClearBucketCache(context));
  int exit_code = shell.execute();
  return exit_code;
}

int main(int argc, char *argv[]) {
  return run_shell(std::cin);
}
