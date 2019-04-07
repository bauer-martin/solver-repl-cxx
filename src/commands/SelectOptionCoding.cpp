#include "commands/SelectOptionCoding.h"

namespace commands {

SelectOptionCoding::SelectOptionCoding(utilities::GlobalContext &global_context)
    : ShellCommand(global_context), _codings() {
}

void SelectOptionCoding::register_option_coding(const std::string &coding_name, OptionCodingInit init) {
  _codings.emplace(coding_name, init);
}

std::string SelectOptionCoding::execute(const std::string &args_string) {
  auto search = _codings.find(args_string);
  if (search == _codings.end()) {
    return error("unknown option coding '" + args_string + "'");
  }
  OptionCodingInit init = search->second;
  spl_conqueror::VariabilityModel &vm = _global_context.get_variability_model();
  option_coding::OptionCoding *option_coding = init(vm);
  _global_context.set_option_coding(option_coding);
  return default_success_response();
}

}
