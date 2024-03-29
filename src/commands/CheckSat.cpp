#include "commands/CheckSat.h"

#include <sstream>
#include <vector>

#include "option_coding/OptionCoding.h"
#include "spl_conqueror/BinaryOption.h"
#include "spl_conqueror/SatChecker.h"
#include "spl_conqueror/VariabilityModel.h"

namespace commands {

CheckSat::CheckSat(utilities::GlobalContext &global_context) : ShellCommand(global_context) {
}

std::string commands::CheckSat::execute(const std::string &args_string) {
  if (args_string.empty()) {
    return error("partial or complete not specified");
  }
  std::stringstream ss(args_string);
  std::string mode_string;
  getline(ss, mode_string, ' ');
  bool is_partial_configuration = mode_string == "partial";
  if (ss.eof()) {
    return error("no configuration specified");
  }
  std::string config_string;
  getline(ss, config_string, ' ');
  spl_conqueror::VariabilityModel &vm = _global_context.get_variability_model();
  const option_coding::OptionCoding &coding = _global_context.get_option_coding();
  std::vector<spl_conqueror::BinaryOption *> config = coding.decode_binary_options(config_string);
  spl_conqueror::SatChecker &sat_checker = _global_context.get_solver_facade().get_sat_checker();
  bool valid = sat_checker.is_valid(config, is_partial_configuration);
  return valid ? "true" : "false";
}

}
