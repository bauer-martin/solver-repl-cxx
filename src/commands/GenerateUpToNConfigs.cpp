#include "commands/GenerateUpToNConfigs.h"

#include <stdexcept>
#include <vector>

#include "spl_conqueror/BinaryOption.h"
#include "spl_conqueror/VariantGenerator.h"
#include "utilities/ParsingUtils.h"

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
  return utilities::encoded_binary_options_vector(configs);
}

}
