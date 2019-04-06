# Try to find OptiMathSat (http://optimathsat.disi.unitn.it/index.html)
#
# Requires OPTIMATHSAT_ROOT to be set.
#
# Once done this will define
#  OptiMathSat_FOUND        - True if headers and libraries were found
#  OptiMathSat_INCLUDE_DIRS - OptiMathSat include directories
#  OptiMathSat_LIBRARIES    - OptiMathSat libraries to be linked

if (NOT DEFINED OPTIMATHSAT_ROOT OR OPTIMATHSAT_ROOT STREQUAL "")
  message(FATAL_ERROR "OPTIMATHSAT_ROOT was not given!")
endif ()

find_path(OptiMathSat_INCLUDE_DIR optimathsat.h PATHS "${OPTIMATHSAT_ROOT}/include")

find_library(OptiMathSat_LIBRARY mathsat PATHS "${OPTIMATHSAT_ROOT}/lib")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(OptiMathSat DEFAULT_MSG OptiMathSat_LIBRARY OptiMathSat_INCLUDE_DIR)

set(OptiMathSat_INCLUDE_DIRS ${OptiMathSat_INCLUDE_DIR})
set(OptiMathSat_LIBRARIES ${OptiMathSat_LIBRARY})
mark_as_advanced(OptiMathSat_INCLUDE_DIR OptiMathSat_LIBRARY)
