cmake_minimum_required(VERSION 3.13)
project(spl_conqueror_solvers)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")

option(WITH_OPTIMATHSAT "Add OptiMathSat to the list of available solvers" ON)

add_subdirectory(src)

enable_testing()
add_subdirectory(tests)
