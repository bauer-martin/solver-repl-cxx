#ifndef SELECT_OPTION_CODING_COMMAND_H
#define SELECT_OPTION_CODING_COMMAND_H

#include <map>
#include <string>

#include "option_coding/OptionCoding.h"
#include "spl_conqueror/VariabilityModel.h"
#include "utilities/ShellCommand.h"

namespace commands {

typedef option_coding::OptionCoding *(*OptionCodingInit)(const spl_conqueror::VariabilityModel &);

class SelectOptionCoding : public utilities::ShellCommand {
 private:
  std::map<std::string, OptionCodingInit> _codings;

 public:
  explicit SelectOptionCoding(utilities::GlobalContext &global_context);
  void register_option_coding(const std::string &coding_name, OptionCodingInit init);
  std::string execute(const std::string &args_string) override;

 public:
  SelectOptionCoding(const SelectOptionCoding &other) = delete;
  SelectOptionCoding(SelectOptionCoding &&other) noexcept = delete;
  SelectOptionCoding &operator=(const SelectOptionCoding &other) = delete;
  SelectOptionCoding &operator=(SelectOptionCoding &&other) noexcept = delete;
};

}

#endif //SELECT_OPTION_CODING_COMMAND_H
