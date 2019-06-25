#include "commands/GenerateAllVariants.h"

#include <vector>

#include "option_coding/OptionCoding.h"
#include "spl_conqueror/BinaryOption.h"
#include "spl_conqueror/VariabilityModel.h"
#include "spl_conqueror/VariantGenerator.h"

namespace commands {

GenerateAllVariants::GenerateAllVariants(utilities::GlobalContext &global_context) : ShellCommand(global_context) {
}

std::string commands::GenerateAllVariants::execute(const std::string &args_string) {
  if (args_string.empty()) {
    return error("no options specified");
  }
  const option_coding::OptionCoding &coding = _global_context.get_option_coding();
  std::vector<spl_conqueror::BinaryOption *> options_to_consider = coding.decode_binary_options(args_string);

  spl_conqueror::VariantGenerator &vg = _global_context.get_solver_facade().get_variant_generator();
  std::set<std::vector<spl_conqueror::BinaryOption *>> all_variants = vg.generate_all_variants(options_to_consider);
  return all_variants.empty() ? "none" : coding.encode_binary_options_set(all_variants);
}

}
