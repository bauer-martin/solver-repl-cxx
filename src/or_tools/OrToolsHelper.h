#ifndef OR_TOOLS_HELPER_H
#define OR_TOOLS_HELPER_H

#include <vector>

#include "OrToolsConstraintSystemContext.h"
#include "spl_conqueror/BinaryOption.h"

namespace or_tools {

void select_features(OrToolsConstraintSystemContext &context,
                     const std::vector<spl_conqueror::BinaryOption *> &selected_options);

}

#endif //OR_TOOLS_HELPER_H
