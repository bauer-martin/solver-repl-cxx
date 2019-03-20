#include "commands/LoadVm.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "spl_conqueror/VariabilityModel.h"
#include "utilities/Helpers.h"

namespace commands {

LoadVm::LoadVm(utilities::GlobalContext &global_context) : ShellCommand(global_context) {
}

std::string LoadVm::execute(const std::string &args_string) {
  if (helpers::file_exists(args_string)) {
    boost::property_tree::ptree tree;
    boost::property_tree::read_xml(args_string, tree);
    spl_conqueror::VariabilityModel *model = spl_conqueror::VariabilityModel::make_from_xml(tree);
    _global_context.set_variability_model(model);
    return default_success_response();
  } else {
    return error("file '" + args_string + "' not found");
  }
}

}
