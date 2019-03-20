#ifndef HELPERS_H
#define HELPERS_H

#include <string>

namespace helpers {

std::string &ltrim(std::string &str, const std::string &chars = "\t\n\v\f\r ");
std::string &rtrim(std::string &str, const std::string &chars = "\t\n\v\f\r ");
std::string &trim(std::string &str, const std::string &chars = "\t\n\v\f\r ");
bool file_exists(const std::string &filename);

}

#endif //HELPERS_H
