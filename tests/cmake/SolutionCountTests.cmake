configure_file(${CMAKE_CURRENT_SOURCE_DIR}/feature-models/Apache_energy.xml ${CMAKE_CURRENT_BINARY_DIR}/feature-models/Apache_energy.xml COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/feature-models/BerkeleyDBC.xml ${CMAKE_CURRENT_BINARY_DIR}/feature-models/BerkeleyDBC.xml COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/feature-models/brotli.xml ${CMAKE_CURRENT_BINARY_DIR}/feature-models/brotli.xml COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/feature-models/Dune_bin.xml ${CMAKE_CURRENT_BINARY_DIR}/feature-models/Dune_bin.xml COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/feature-models/exastencils_energy.xml ${CMAKE_CURRENT_BINARY_DIR}/feature-models/exastencils_energy.xml COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/feature-models/Hipacc_bin.xml ${CMAKE_CURRENT_BINARY_DIR}/feature-models/Hipacc_bin.xml COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/feature-models/HSQLDB_energy.xml ${CMAKE_CURRENT_BINARY_DIR}/feature-models/HSQLDB_energy.xml COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/feature-models/LLVM_energy.xml ${CMAKE_CURRENT_BINARY_DIR}/feature-models/LLVM_energy.xml COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/feature-models/LLVM.xml ${CMAKE_CURRENT_BINARY_DIR}/feature-models/LLVM.xml COPYONLY)

set(CASE_STUDIES
    Apache_energy
    BerkeleyDBC
    brotli
    Dune_bin
    exastencils_energy
    Hipacc_bin
    HSQLDB_energy
    LLVM
    LLVM_energy)

set(EXPECTED_SOLUTION_COUNTS
    580
    2560
    180
    2304
    86058
    13485
    864
    1024
    65536)

list(LENGTH CASE_STUDIES CASE_STUDY_COUNT)
math(EXPR END_INDEX "${CASE_STUDY_COUNT} - 1")

foreach (SOLVER ${SOLVERS})
  foreach (INDEX RANGE ${END_INDEX})
    list(GET CASE_STUDIES ${INDEX} CASE_STUDY)
    list(GET EXPECTED_SOLUTION_COUNTS ${INDEX} EXPECTED_SOLUTION_COUNT)
    configure_file(SolutionCountTestCase.cpp.in ${SOLVER}_SolutionCountTestCase_${CASE_STUDY}.cpp @ONLY)

    set(EXECUTABLE_NAME "")
    string(TOLOWER ${CASE_STUDY} EXECUTABLE_NAME)
    add_executable(test_${SOLVER}_solution_count_${EXECUTABLE_NAME} ${SOLVER}_SolutionCountTestCase_${CASE_STUDY}.cpp)
    target_link_libraries(test_${SOLVER}_solution_count_${EXECUTABLE_NAME} PRIVATE core)
    add_test(${SOLVER}_solution_count_${EXECUTABLE_NAME} test_${SOLVER}_solution_count_${EXECUTABLE_NAME})
  endforeach ()
endforeach ()
