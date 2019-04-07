set(SOLVERS "")

if (DEFINED OPTIMATHSAT_ROOT)
  list(APPEND SOLVERS opti_math_sat)
endif ()

if (DEFINED OR_TOOLS_ROOT)
  list(APPEND SOLVERS or_tools)
endif ()

include(SolutionCountTests)
