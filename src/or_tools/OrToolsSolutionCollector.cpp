#include "OrToolsSolutionCollector.h"

namespace or_tools {

OrToolsSolutionCollector::OrToolsSolutionCollector(const OrToolsConstraintSystemContext &context, uint seed)
    : OrToolsSolutionCollector(context, seed, -1) {
}

OrToolsSolutionCollector::OrToolsSolutionCollector(const OrToolsConstraintSystemContext &context, uint seed, int limit)
    : _context(context),
      _limit(limit),
      _solutions(),
      _model(new operations_research::sat::Model()),
      _solution_limit_reached(false) {
  operations_research::sat::SatParameters parameters;
  parameters.set_enumerate_all_solutions(limit == -1 || limit > 1);
  parameters.set_random_seed(seed);
  _model->Add(NewSatParameters(parameters));

  _model->GetOrCreate<operations_research::TimeLimit>()->RegisterExternalBooleanAsLimit(&_solution_limit_reached);

  _model->Add(operations_research::sat::NewFeasibleSolutionObserver(
      [this](const operations_research::sat::CpSolverResponse &r) {
        std::vector<spl_conqueror::BinaryOption *> config;
        for (auto &&option : _context.get_variability_model().get_binary_options()) {
          operations_research::sat::BoolVar variable = _context.option_to_var(*option);
          bool value = operations_research::sat::SolutionBooleanValue(r, variable);
          if (value) {
            config.push_back(option);
          }
        }
        _solutions.push_back(config);
        if (_limit > 0 && _solutions.size() >= _limit) {
          _solution_limit_reached = true;
        }
      }));
}

OrToolsSolutionCollector::~OrToolsSolutionCollector() {
  delete _model;
}

operations_research::sat::Model *OrToolsSolutionCollector::get_model() const {
  return _model;
}

const std::vector<std::vector<spl_conqueror::BinaryOption *>> &OrToolsSolutionCollector::get_solutions() const {
  return _solutions;
}

}
