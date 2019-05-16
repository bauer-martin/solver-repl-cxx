target_sources(core
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
target_include_directories(core
  PUBLIC
    ${ORTools_INCLUDE_DIRS}
)
target_link_libraries(core
  PRIVATE
    ${ORTools_LIBRARIES}
)
