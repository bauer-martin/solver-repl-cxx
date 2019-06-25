#include "commands/FindAllMaximizedConfigs.h"

#include <sstream>
#include <vector>

#include "option_coding/OptionCoding.h"
#include "spl_conqueror/BinaryOption.h"
#include "spl_conqueror/VariabilityModel.h"
#include "spl_conqueror/VariantGenerator.h"

namespace commands {

FindAllMaximizedConfigs::FindAllMaximizedConfigs(utilities::GlobalContext &global_context)
    : ShellCommand(global_context) {
}

std::string commands::FindAllMaximizedConfigs::execute(const std::string &args_string) {
  spl_conqueror::VariabilityModel &vm = _global_context.get_variability_model();
  const option_coding::OptionCoding &coding = _global_context.get_option_coding();
  std::stringstream ss(args_string);
  std::vector<spl_conqueror::BinaryOption *> config;
  if (!ss.eof()) {
    std::string config_string;
    getline(ss, config_string, ' ');
    config = coding.decode_binary_options(config_string);
  }
  std::vector<spl_conqueror::BinaryOption *> unwanted_options;
  if (!ss.eof()) {
    std::string options_string;
    getline(ss, options_string, ' ');
    unwanted_options = coding.decode_binary_options(options_string);
  }
  spl_conqueror::VariantGenerator &vg = _global_context.get_solver_facade().get_variant_generator();
  std::vector<std::vector<spl_conqueror::BinaryOption *>> optimal_configs
      = vg.find_all_maximized_configs(config, unwanted_options);
  return optimal_configs.empty() ? "none" : coding.encode_binary_options_vector(optimal_configs);
}

}
