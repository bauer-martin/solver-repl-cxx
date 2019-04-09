#include "utilities/Helpers.h"

#include <fstream>

namespace helpers {

std::string &ltrim(std::string &str, const std::string &chars) {
  str.erase(0, str.find_first_not_of(chars));
  return str;
}

std::string &rtrim(std::string &str, const std::string &chars) {
  str.erase(str.find_last_not_of(chars) + 1);
  return str;
}

std::string &trim(std::string &str, const std::string &chars) {
  return ltrim(rtrim(str, chars), chars);
}

bool file_exists(const std::string &filename) {
  std::ifstream ifile(filename);
  if (ifile) {
    return true;
  } else {
    return false;
  }
}

bool contains(const std::vector<spl_conqueror::BinaryOption *> &vector, const spl_conqueror::BinaryOption &option) {
  return std::find_if(vector.cbegin(), vector.cend(),
                      [&option](spl_conqueror::BinaryOption *o) -> bool {
                        return o->get_name() == option.get_name();
                      }) != vector.cend();
}

}
