target_sources(core
  PRIVATE
    ${CMAKE_SOURCE_DIR}/include/spl_conqueror/BinaryOption.h BinaryOption.cpp
    ${CMAKE_SOURCE_DIR}/include/spl_conqueror/BucketSession.h BucketSession.cpp
    ${CMAKE_SOURCE_DIR}/include/spl_conqueror/SatChecker.h SatChecker.cpp
    ${CMAKE_SOURCE_DIR}/include/spl_conqueror/SolverFacade.h SolverFacade.cpp
    ${CMAKE_SOURCE_DIR}/include/spl_conqueror/VariabilityModel.h VariabilityModel.cpp
    ${CMAKE_SOURCE_DIR}/include/spl_conqueror/VariantGenerator.h VariantGenerator.cpp
)
