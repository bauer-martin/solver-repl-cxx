#include "commands/FindAllMaximizedConfigs.h"

#include <sstream>
#include <vector>

#include "spl_conqueror/BinaryOption.h"
#include "spl_conqueror/VariabilityModel.h"
#include "spl_conqueror/VariantGenerator.h"
#include "utilities/ParsingUtils.h"

namespace commands {

FindAllMaximizedConfigs::FindAllMaximizedConfigs(utilities::GlobalContext &global_context)
    : ShellCommand(global_context) {
}

std::string commands::FindAllMaximizedConfigs::execute(const std::string &args_string) {
  spl_conqueror::VariabilityModel &vm = _global_context.get_variability_model();
  std::stringstream ss(args_string);
  std::vector<spl_conqueror::BinaryOption *> config;
  if (!ss.eof()) {
    std::string config_string;
    getline(ss, config_string, ' ');
    config = utilities::decoded_binary_options(config_string, vm);
  }
  std::vector<spl_conqueror::BinaryOption *> unwanted_options;
  if (!ss.eof()) {
    std::string options_string;
    getline(ss, options_string, ' ');
    unwanted_options = utilities::decoded_binary_options(options_string, vm);
  }
  spl_conqueror::VariantGenerator &vg = _global_context.get_variant_generator();
  std::vector<std::vector<spl_conqueror::BinaryOption *>> optimal_configs
      = vg.find_all_maximized_configs(config, unwanted_options);
  return utilities::encoded_binary_options_vector(optimal_configs);
}

}
