add_library(core STATIC "")

add_subdirectory(commands)
add_subdirectory(option_coding)
add_subdirectory(spl_conqueror)
add_subdirectory(utilities)

if (DEFINED OPTIMATHSAT_ROOT)
  message(STATUS "Adding OptiMathSat")
  add_definitions(-DUSE_OPTIMATHSAT)
  add_subdirectory(opti_math_sat)
endif ()

if (DEFINED OR_TOOLS_ROOT)
  message(STATUS "Adding OR-Tools")
  add_definitions(-DUSE_OR_TOOLS)
  add_subdirectory(or_tools)
endif ()

find_package(Boost 1.57 REQUIRED)

target_include_directories(core
  PUBLIC
    ${Boost_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/include
)

add_executable(solver-repl-cxx main.cpp)
target_link_libraries(solver-repl-cxx PRIVATE core)
