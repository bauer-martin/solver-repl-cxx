#ifndef PARSING_UTILS_H
#define PARSING_UTILS_H

#include <set>
#include <string>
#include <vector>

#include "spl_conqueror/BinaryOption.h"
#include "spl_conqueror/VariabilityModel.h"

namespace utilities {

std::vector<spl_conqueror::BinaryOption *> decoded_binary_options(
    const std::string &str, const spl_conqueror::VariabilityModel &vm);
std::string encoded_binary_options(const std::vector<spl_conqueror::BinaryOption *> &options);
std::string encoded_binary_options_vector(const std::vector<std::vector<spl_conqueror::BinaryOption *>> &configs);
std::string encoded_binary_options_set(const std::set<std::vector<spl_conqueror::BinaryOption *>> &configs);

}

#endif //PARSING_UTILS_H
