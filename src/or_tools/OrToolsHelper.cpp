#include "OrToolsHelper.h"

#include "utilities/Helpers.h"

namespace or_tools {

void select_features(OrToolsConstraintSystemContext &context,
                     const std::vector<spl_conqueror::BinaryOption *> &selected_options) {
  std::vector<ort::BoolVar> and_vars;
  and_vars.reserve(selected_options.size());
  for (auto &&option : selected_options) {
    const ort::BoolVar &variable = context.option_to_var(*option);
    and_vars.push_back(variable);
  }
  context.get_model().AddBoolAnd(and_vars);
}

}
