target_sources(spl_conqueror_solvers_core
  PRIVATE
    OrToolsBucketSession.h OrToolsBucketSession.cpp
    OrToolsConstraintSystemContext.h OrToolsConstraintSystemContext.cpp
    OrToolsHelper.h OrToolsHelper.cpp
    OrToolsSatChecker.h OrToolsSatChecker.cpp
    ${CMAKE_SOURCE_DIR}/include/or_tools/OrToolsSolverFacade.h OrToolsSolverFacade.cpp
    OrToolsVariantGenerator.h OrToolsVariantGenerator.cpp
    OrToolsSolutionCollector.h OrToolsSolutionCollector.cpp
)

find_package(ORTools REQUIRED)
target_include_directories(spl_conqueror_solvers_core
  PUBLIC
    ${ORTools_INCLUDE_DIRS}
)
target_link_libraries(spl_conqueror_solvers_core
  PRIVATE
    ${ORTools_LIBRARIES}
)
