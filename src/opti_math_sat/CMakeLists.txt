target_sources(spl_conqueror_solvers_core
  PRIVATE
    OptiMathSatBucketSession.h OptiMathSatBucketSession.cpp
    OptiMathSatConstraintSystemContext.h OptiMathSatConstraintSystemContext.cpp
    OptiMathSatHelper.h OptiMathSatHelper.cpp
    OptiMathSatSatChecker.h OptiMathSatSatChecker.cpp
    ${CMAKE_SOURCE_DIR}/include/opti_math_sat/OptiMathSatSolverFactory.h OptiMathSatSolverFactory.cpp
    OptiMathSatVariantGenerator.h OptiMathSatVariantGenerator.cpp
)

find_package(OptiMathSat REQUIRED)
target_include_directories(spl_conqueror_solvers_core
  PUBLIC
    ${OptiMathSat_INCLUDE_DIR}
)
target_link_libraries(spl_conqueror_solvers_core
  PRIVATE
    ${OptiMathSat_LIBRARIES}
)

find_package(GMP REQUIRED)
target_link_libraries(spl_conqueror_solvers_core
  PRIVATE
    ${GMP_LIBRARIES}
)
