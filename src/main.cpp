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
#include "commands/SelectSolver.h"
#include "spl_conqueror/BinaryOption.h"
#include "utilities/Shell.h"
#include "utilities/GlobalContext.h"

static int run_shell(std::istream &input) {
  utilities::Shell shell(input);
  utilities::GlobalContext context;
  shell.register_command("load-vm", new commands::LoadVm(context));
  auto *select_solver_command = new commands::SelectSolver(context);
  shell.register_command("select-solver", select_solver_command);
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
