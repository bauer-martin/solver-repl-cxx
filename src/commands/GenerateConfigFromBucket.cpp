#include "commands/GenerateConfigFromBucket.h"

#include <list>
#include <sstream>
#include <stdexcept>
#include <vector>

#include "option_coding/OptionCoding.h"
#include "spl_conqueror/BinaryOption.h"
#include "spl_conqueror/VariabilityModel.h"
#include "spl_conqueror/VariantGenerator.h"

namespace commands {

GenerateConfigFromBucket::GenerateConfigFromBucket(utilities::GlobalContext &global_context)
    : ShellCommand(global_context) {
}

static std::list<std::pair<int, std::vector<spl_conqueror::BinaryOption *>>> decode_feature_weight_map(
    const std::string &str, const option_coding::OptionCoding &coding) {
  std::list<std::pair<int, std::vector<spl_conqueror::BinaryOption *>>> pairs;
  std::stringstream ss(str);
  std::string config_string;
  std::string weight_string;
  while (!ss.eof()) {
    getline(ss, config_string, '=');
    std::vector<spl_conqueror::BinaryOption *> config = coding.decode_binary_options(config_string);
    getline(ss, weight_string, ';');
    int weight = std::stoi(weight_string);
    pairs.emplace_back(weight, config);
  }
  return pairs;
}

std::string commands::GenerateConfigFromBucket::execute(const std::string &args_string) {
  if (args_string.empty()) {
    return error("no number specified");
  }
  std::stringstream ss(args_string);
  std::string count_string;
  getline(ss, count_string, ' ');
  int selected_options_count;
  try {
    selected_options_count = std::stoi(count_string);
  } catch (std::invalid_argument &ex) {
    return error("invalid number '" + count_string + "'");
  }
  const option_coding::OptionCoding &coding = _global_context.get_option_coding();
  std::list<std::pair<int, std::vector<spl_conqueror::BinaryOption *>>> feature_weight;
  if (!ss.eof()) {
    std::string map_string;
    getline(ss, map_string, ' ');
    feature_weight = decode_feature_weight_map(map_string, coding);
  }
  spl_conqueror::BucketSession *bucket_session = _global_context.get_bucket_session();
  if (!bucket_session) {
    spl_conqueror::VariantGenerator &vg = _global_context.get_solver_facade().get_variant_generator();
    bucket_session = vg.create_bucket_session();
    _global_context.set_bucket_session(bucket_session);
  }
  feature_weight.sort();
  std::vector<std::vector<spl_conqueror::BinaryOption *>> feature_ranking;
  feature_ranking.reserve(feature_weight.size());
  for (auto &&pair : feature_weight) {
    feature_ranking.push_back(pair.second);
  }
  std::vector<spl_conqueror::BinaryOption *> *config
      = bucket_session->generate_config(selected_options_count, feature_ranking);
  std::string response;
  if (config) {
    response = coding.encode_binary_options(*config);
    delete config;
  } else {
    response = "none";
  }
  return response;
}

}
