#include "commands/GenerateAllVariants.h"

#include <vector>

#include "spl_conqueror/BinaryOption.h"
#include "spl_conqueror/VariabilityModel.h"
#include "spl_conqueror/VariantGenerator.h"
#include "utilities/ParsingUtils.h"

namespace commands {

GenerateAllVariants::GenerateAllVariants(utilities::GlobalContext &global_context) : ShellCommand(global_context) {
}

std::string commands::GenerateAllVariants::execute(const std::string &args_string) {
  if (args_string.empty()) {
    return error("no options specified");
  }
  spl_conqueror::VariabilityModel &vm = _global_context.get_variability_model();
  std::vector<spl_conqueror::BinaryOption *> options_to_consider = utilities::decoded_binary_options(args_string, vm);

  spl_conqueror::VariantGenerator &vg = _global_context.get_variant_generator();
  std::set<std::vector<spl_conqueror::BinaryOption *>> all_variants = vg.generate_all_variants(options_to_consider);
  return utilities::encoded_binary_options_set(all_variants);
}

}
