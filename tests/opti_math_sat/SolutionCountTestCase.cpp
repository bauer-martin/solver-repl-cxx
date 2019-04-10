#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <iostream>

#include "opti_math_sat/OptiMathSatSolverFacade.h"
#include "spl_conqueror/VariabilityModel.h"
#include "spl_conqueror/VariantGenerator.h"

int test_case(const std::string &feature_model, int expected_solution_count) {
  boost::property_tree::ptree tree;
  boost::property_tree::read_xml("feature-models/" + feature_model, tree);
  spl_conqueror::VariabilityModel *model = spl_conqueror::VariabilityModel::make_from_xml(tree);
  opti_math_sat::OptiMathSatSolverFacade solver_facade(*model);
  spl_conqueror::VariantGenerator &vg = solver_facade.get_variant_generator();
  const std::vector<std::vector<spl_conqueror::BinaryOption *>> &solutions = vg.generate_up_to_n_configs(-1);
  int actual_solution_count = solutions.size();
  if (actual_solution_count == expected_solution_count) {
    return EXIT_SUCCESS;
  } else {
    std::cerr << "Expected: " << expected_solution_count << ", but got: " << actual_solution_count << std::endl;
    return EXIT_FAILURE;
  }
}
