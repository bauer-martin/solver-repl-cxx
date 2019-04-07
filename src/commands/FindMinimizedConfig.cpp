#include "commands/FindMinimizedConfig.h"

#include <sstream>
#include <vector>

#include "option_coding/OptionCoding.h"
#include "spl_conqueror/BinaryOption.h"
#include "spl_conqueror/VariabilityModel.h"
#include "spl_conqueror/VariantGenerator.h"

namespace commands {

FindMinimizedConfig::FindMinimizedConfig(utilities::GlobalContext &global_context) : ShellCommand(global_context) {
}

std::string commands::FindMinimizedConfig::execute(const std::string &args_string) {
  if (args_string.empty()) {
    return error("no configuration specified");
  }
  std::stringstream ss(args_string);
  std::string config_string;
  getline(ss, config_string, ' ');
  const option_coding::OptionCoding &coding = _global_context.get_option_coding();
  std::vector<spl_conqueror::BinaryOption *> config = coding.decode_binary_options(config_string);
  std::vector<spl_conqueror::BinaryOption *> unwanted_options;
  if (!ss.eof()) {
    std::string options_string;
    getline(ss, options_string, ' ');
    unwanted_options = coding.decode_binary_options(options_string);
  }

  spl_conqueror::VariantGenerator &vg = _global_context.get_variant_generator();
  std::vector<spl_conqueror::BinaryOption *> *optimal_config = vg.find_minimized_config(config, unwanted_options);
  std::string response;
  if (optimal_config) {
    response = coding.encode_binary_options(*optimal_config);
    delete optimal_config;
  } else {
    response = "none";
  }
  return response;
}

}
