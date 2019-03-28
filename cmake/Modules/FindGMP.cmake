# Try to find the GMP library (https://gmplib.org)
#
# Once done this will define
#  GMP_FOUND        - True if headers and libraries were found
#  GMP_INCLUDE_DIRS - GMP include directories
#  GMP_LIBRARIES    - GMP libraries to be linked

find_path(GMP_INCLUDE_DIR gmp.h)
find_library(GMP_LIBRARY gmp)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GMP DEFAULT_MSG GMP_INCLUDE_DIR GMP_LIBRARY)

set(GMP_INCLUDE_DIRS ${GMP_INCLUDE_DIR})
set(GMP_LIBRARIES ${GMP_LIBRARY})
mark_as_advanced(GMP_INCLUDE_DIR GMP_LIBRARY)
