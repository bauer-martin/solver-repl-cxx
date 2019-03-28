# Try to find OptiMathSat (http://optimathsat.disi.unitn.it/index.html)
#
# Once done this will define
#  OptiMathSat_FOUND        - True if headers and libraries were found
#  OptiMathSat_INCLUDE_DIRS - OptiMathSat include directories
#  OptiMathSat_LIBRARIES    - OptiMathSat libraries to be linked

if (OPTIMATHSAT_ROOT)
    find_path(OptiMathSat_INCLUDE_DIR optimathsat.h PATHS "${OPTIMATHSAT_ROOT}/include")
else ()
    find_path(OptiMathSat_INCLUDE_DIR optimathsat.h)
endif ()

if (OPTIMATHSAT_ROOT)
    find_library(OptiMathSat_LIBRARY mathsat PATHS "${OPTIMATHSAT_ROOT}/lib")
else ()
    find_library(OptiMathSat_LIBRARY mathsat)
endif ()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(OptiMathSat DEFAULT_MSG OptiMathSat_LIBRARY OptiMathSat_INCLUDE_DIR)

set(OptiMathSat_INCLUDE_DIRS ${OptiMathSat_INCLUDE_DIR})
set(OptiMathSat_LIBRARIES ${OptiMathSat_LIBRARY})
mark_as_advanced(OptiMathSat_INCLUDE_DIR OptiMathSat_LIBRARY)
