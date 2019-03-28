add_library(spl_conqueror_solvers_core STATIC "")

add_subdirectory(commands)
add_subdirectory(spl_conqueror)
add_subdirectory(utilities)

if(WITH_OPTIMATHSAT)
    message(STATUS "Adding OptiMathSat")
    add_definitions(-DUSE_OPTIMATHSAT)
    add_subdirectory(opti_math_sat)
endif(WITH_OPTIMATHSAT)

find_package(Boost 1.68 REQUIRED)

target_include_directories(spl_conqueror_solvers_core
  PUBLIC
    ${Boost_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/include
)

add_executable(spl_conqueror_solvers main.cpp)
target_link_libraries(spl_conqueror_solvers PRIVATE spl_conqueror_solvers_core)
