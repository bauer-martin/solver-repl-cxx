#ifndef SHELL_H
#define SHELL_H

#include <map>
#include <string>

#include "utilities/ShellCommand.h"

namespace utilities {

class Shell final {
 private:
  std::istream &_input;
  std::map<std::string, ShellCommand *> _commands;

 public :
  explicit Shell(std::istream &input);
  ~Shell();
  void register_command(const std::string &command_name, ShellCommand *command);
  int execute();

 public:
  Shell(const Shell &other) = delete;
  Shell(Shell &&other) noexcept = delete;
  Shell &operator=(const Shell &other) = delete;
  Shell &operator=(Shell &&other) noexcept = delete;
};

}

#endif //SHELL_H
