target_sources(spl_conqueror_solvers_core
  PRIVATE
    ${CMAKE_SOURCE_DIR}/include/utilities/GlobalContext.h GlobalContext.cpp
    ${CMAKE_SOURCE_DIR}/include/utilities/Helpers.h Helpers.cpp
    ${CMAKE_SOURCE_DIR}/include/utilities/Shell.h Shell.cpp
    ${CMAKE_SOURCE_DIR}/include/utilities/ShellCommand.h ShellCommand.cpp
    ${CMAKE_SOURCE_DIR}/include/utilities/SolverParameterKeys.h SolverParameterKeys.cpp
)
