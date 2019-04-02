set(SOLVERS "")

if (WITH_OPTIMATHSAT)
  list(APPEND SOLVERS opti_math_sat)
endif (WITH_OPTIMATHSAT)

if (WITH_OR_TOOLS)
  list(APPEND SOLVERS or_tools)
endif (WITH_OR_TOOLS)

include(SolutionCountTests)
