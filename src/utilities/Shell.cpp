#include "utilities/Shell.h"

#include <iostream>
#include <sstream>

namespace utilities {

Shell::Shell(std::istream &input) : _input(input), _commands() {
}

Shell::~Shell() {
  for (auto &&pair: _commands) {
    delete pair.second;
  }
}

void Shell::register_command(const std::string &command_name, ShellCommand *command) {
  _commands.emplace(command_name, command);
}

int Shell::execute() {
  bool should_process_input = true;
  int exit_code = EXIT_SUCCESS;
  do {
    std::string line;
    getline(_input, line);
    if (line.empty()) {
      exit_code = EXIT_FAILURE;
      std::cerr << "no command specified" << std::endl;
      break;
    }
    std::stringstream ss(line);
    std::string command_string;
    std::getline(ss, command_string, ' ');
    std::string args_string;
    if (!ss.eof()) {
      std::getline(ss, args_string);
    }
    auto search = _commands.find(command_string);
    if (search != _commands.end()) {
      ShellCommand *command = search->second;
      std::string response = command->execute(args_string);
      std::cout << response << std::endl;
    } else if (command_string == "exit") {
      should_process_input = false;
    } else {
      std::cerr << "terminating due to unknown command '" << command_string << "'" << std::endl;
      exit_code = EXIT_FAILURE;
      should_process_input = false;
    }
  } while (should_process_input);
  return exit_code;
}

}
