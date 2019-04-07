cmake_minimum_required(VERSION 3.13)
project(spl_conqueror_solvers)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules" "${CMAKE_CURRENT_SOURCE_DIR}/tests/cmake")

option(WITH_TESTS "Configure tests" OFF)

add_subdirectory(src)

if (WITH_TESTS)
  message(STATUS "Configuring tests")
  enable_testing()
  add_subdirectory(tests)
endif (WITH_TESTS)
