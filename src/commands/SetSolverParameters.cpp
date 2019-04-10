#include "commands/SetSolverParameters.h"

#include <map>

namespace commands {

SetSolverParameters::SetSolverParameters(utilities::GlobalContext &global_context) : ShellCommand(global_context) {
}

static std::map<std::string, std::string> decode_parameter_map(const std::string &str) {
  std::map<std::string, std::string> parameters;
  std::stringstream ss(str);
  std::string key;
  std::string value;
  while (!ss.eof()) {
    getline(ss, key, '=');
    getline(ss, value, ';');
    parameters.emplace(key, value);
  }
  return parameters;
}

std::string SetSolverParameters::execute(const std::string &args_string) {
  const std::map<std::string, std::string> &parameters = decode_parameter_map(args_string);
  _global_context.get_solver_facade().set_parameters(parameters);
  return default_success_response();
}

}
