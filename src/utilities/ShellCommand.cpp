#include "utilities/ShellCommand.h"

namespace utilities {

ShellCommand::~ShellCommand() = default;

std::string ShellCommand::error(const std::string &message) {
  return "error: " + message;
}

std::string ShellCommand::default_success_response() {
  return "ok";
}

}
