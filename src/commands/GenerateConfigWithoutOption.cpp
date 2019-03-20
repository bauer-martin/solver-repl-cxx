#include "commands/GenerateConfigWithoutOption.h"

#include <sstream>
#include <vector>

#include "spl_conqueror/BinaryOption.h"
#include "spl_conqueror/VariabilityModel.h"
#include "spl_conqueror/VariantGenerator.h"
#include "utilities/ParsingUtils.h"

namespace commands {

GenerateConfigWithoutOption::GenerateConfigWithoutOption(utilities::GlobalContext &global_context)
    : ShellCommand(global_context) {
}

std::string commands::GenerateConfigWithoutOption::execute(const std::string &args_string) {
  if (args_string.empty()) {
    return error("no configuration specified");
  }
  std::stringstream ss(args_string);
  std::string config_string;
  getline(ss, config_string, ' ');
  spl_conqueror::VariabilityModel &vm = _global_context.get_variability_model();
  std::vector<spl_conqueror::BinaryOption *> config = utilities::decoded_binary_options(config_string, vm);
  if (ss.eof()) {
    return error("no option specified");
  }
  std::string option_name;
  getline(ss, option_name);
  spl_conqueror::BinaryOption *option_to_remove = vm.get_binary_option(option_name);

  spl_conqueror::VariantGenerator &vg = _global_context.get_variant_generator();
  std::vector<spl_conqueror::BinaryOption *> removed_options;
  std::vector<spl_conqueror::BinaryOption *> *new_config = vg.generate_config_without_option(config,
                                                                                             *option_to_remove,
                                                                                             removed_options);
  std::string response;
  if (new_config) {
    response = utilities::encoded_binary_options(*new_config)
        + " "
        + utilities::encoded_binary_options(removed_options);
    delete new_config;
  } else {
    response = "none";
  }
  return response;
}

}
