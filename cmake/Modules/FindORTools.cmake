# Try to find Google OR-Tools (https://developers.google.com/optimization/)
#
# Requires OR_TOOLS_ROOT to be set.
#
# Once done this will define
#  ORTools_FOUND        - True if headers and libraries were found
#  ORTools_INCLUDE_DIRS - OR-Tools include directories
#  ORTools_LIBRARIES    - OR-Tools libraries to be linked

if (NOT DEFINED OR_TOOLS_ROOT OR OR_TOOLS_ROOT STREQUAL "")
  message(FATAL_ERROR "OR_TOOLS_ROOT was not given!")
endif ()

find_path(ORTools_INCLUDE_DIR ortools PATHS "${OR_TOOLS_ROOT}/include")

find_library(Cbc_LIBRARY Cbc PATHS "${OR_TOOLS_ROOT}/lib")
find_library(CbcSolver_LIBRARY CbcSolver PATHS "${OR_TOOLS_ROOT}/lib")
find_library(Cgl_LIBRARY Cgl PATHS "${OR_TOOLS_ROOT}/lib")
find_library(Clp_LIBRARY Clp PATHS "${OR_TOOLS_ROOT}/lib")
find_library(ClpSolver_LIBRARY ClpSolver PATHS "${OR_TOOLS_ROOT}/lib")
find_library(CoinUtils_LIBRARY CoinUtils PATHS "${OR_TOOLS_ROOT}/lib")
find_library(gflags_LIBRARY gflags PATHS "${OR_TOOLS_ROOT}/lib")
find_library(glog_LIBRARY glog PATHS "${OR_TOOLS_ROOT}/lib")
find_library(OsiCbc_LIBRARY OsiCbc PATHS "${OR_TOOLS_ROOT}/lib")
find_library(OsiClp_LIBRARY OsiClp PATHS "${OR_TOOLS_ROOT}/lib")
find_library(protobuf_LIBRARY protobuf PATHS "${OR_TOOLS_ROOT}/lib")
find_library(ortools_LIBRARY ortools PATHS "${OR_TOOLS_ROOT}/lib")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ORTools DEFAULT_MSG
    ORTools_INCLUDE_DIR
    Cbc_LIBRARY
    CbcSolver_LIBRARY
    Cgl_LIBRARY
    Clp_LIBRARY
    ClpSolver_LIBRARY
    CoinUtils_LIBRARY
    gflags_LIBRARY
    glog_LIBRARY
    OsiCbc_LIBRARY
    OsiClp_LIBRARY
    protobuf_LIBRARY
    ortools_LIBRARY)

set(ORTools_INCLUDE_DIRS ${ORTools_INCLUDE_DIR})
set(ORTools_LIBRARIES
    ${Cbc_LIBRARY}
    ${CbcSolver_LIBRARY}
    ${Cgl_LIBRARY}
    ${Clp_LIBRARY}
    ${ClpSolver_LIBRARY}
    ${CoinUtils_LIBRARY}
    ${gflags_LIBRARY}
    ${glog_LIBRARY}
    ${OsiCbc_LIBRARY}
    ${OsiClp_LIBRARY}
    ${protobuf_LIBRARY}
    ${ortools_LIBRARY})
mark_as_advanced(ORTools_INCLUDE_DIR
    Cbc_LIBRARY
    CbcSolver_LIBRARY
    Cgl_LIBRARY
    Clp_LIBRARY
    ClpSolver_LIBRARY
    CoinUtils_LIBRARY
    gflags_LIBRARY
    glog_LIBRARY
    OsiCbc_LIBRARY
    OsiClp_LIBRARY
    protobuf_LIBRARY
    ortools_LIBRARY)
