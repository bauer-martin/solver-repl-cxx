target_sources(spl_conqueror_solvers_core
  PRIVATE
    ${CMAKE_SOURCE_DIR}/include/commands/CheckSat.h CheckSat.cpp
    ${CMAKE_SOURCE_DIR}/include/commands/ClearBucketCache.h ClearBucketCache.cpp
    ${CMAKE_SOURCE_DIR}/include/commands/FindAllMaximizedConfigs.h FindAllMaximizedConfigs.cpp
    ${CMAKE_SOURCE_DIR}/include/commands/FindMinimizedConfig.h FindMinimizedConfig.cpp
    ${CMAKE_SOURCE_DIR}/include/commands/GenerateAllVariants.h GenerateAllVariants.cpp
    ${CMAKE_SOURCE_DIR}/include/commands/GenerateConfigFromBucket.h GenerateConfigFromBucket.cpp
    ${CMAKE_SOURCE_DIR}/include/commands/GenerateConfigWithoutOption.h GenerateConfigWithoutOption.cpp
    ${CMAKE_SOURCE_DIR}/include/commands/GenerateUpToNConfigs.h GenerateUpToNConfigs.cpp
    ${CMAKE_SOURCE_DIR}/include/commands/LoadVm.h LoadVm.cpp
    ${CMAKE_SOURCE_DIR}/include/commands/SelectOptionCoding.h SelectOptionCoding.cpp
    ${CMAKE_SOURCE_DIR}/include/commands/SelectSolver.h SelectSolver.cpp
)
