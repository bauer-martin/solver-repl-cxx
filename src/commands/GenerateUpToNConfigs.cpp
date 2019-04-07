#include "commands/GenerateUpToNConfigs.h"

#include <stdexcept>
#include <vector>

#include "option_coding/OptionCoding.h"
#include "spl_conqueror/BinaryOption.h"
#include "spl_conqueror/VariantGenerator.h"

namespace commands {

GenerateUpToNConfigs::GenerateUpToNConfigs(utilities::GlobalContext &global_context) : ShellCommand(global_context) {
}

std::string GenerateUpToNConfigs::execute(const std::string &args_string) {
  int count;
  try {
    count = std::stoi(args_string);
  } catch (std::invalid_argument &ex) {
    return error("invalid number '" + args_string + "'");
  }
  spl_conqueror::VariantGenerator &vg = _global_context.get_variant_generator();
  std::vector<std::vector<spl_conqueror::BinaryOption *>> configs = vg.generate_up_to_n_configs(count);
  const option_coding::OptionCoding &coding = _global_context.get_option_coding();
  return coding.encode_binary_options_vector(configs);
}

}
