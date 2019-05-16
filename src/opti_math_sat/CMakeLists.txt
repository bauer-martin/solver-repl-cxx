target_sources(core
  PRIVATE
    OptiMathSatBucketSession.h OptiMathSatBucketSession.cpp
    OptiMathSatConstraintSystemContext.h OptiMathSatConstraintSystemContext.cpp
    OptiMathSatHelper.h OptiMathSatHelper.cpp
    OptiMathSatSatChecker.h OptiMathSatSatChecker.cpp
    ${CMAKE_SOURCE_DIR}/include/opti_math_sat/OptiMathSatSolverFacade.h OptiMathSatSolverFacade.cpp
    OptiMathSatVariantGenerator.h OptiMathSatVariantGenerator.cpp
)

find_package(OptiMathSat REQUIRED)
target_include_directories(core
  PUBLIC
    ${OptiMathSat_INCLUDE_DIR}
)
target_link_libraries(core
  PRIVATE
    ${OptiMathSat_LIBRARIES}
)

find_package(GMP REQUIRED)
target_link_libraries(core
  PRIVATE
    ${GMP_LIBRARIES}
)
