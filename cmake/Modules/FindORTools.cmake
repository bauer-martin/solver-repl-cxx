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
find_library(absl_bad_any_cast_impl_LIBRARY absl_bad_any_cast_impl PATHS "${OR_TOOLS_ROOT}/lib")
find_library(absl_bad_optional_access_LIBRARY absl_bad_optional_access PATHS "${OR_TOOLS_ROOT}/lib")
find_library(absl_bad_variant_access_LIBRARY absl_bad_variant_access PATHS "${OR_TOOLS_ROOT}/lib")
find_library(absl_base_LIBRARY absl_base PATHS "${OR_TOOLS_ROOT}/lib")
find_library(absl_city_LIBRARY absl_city PATHS "${OR_TOOLS_ROOT}/lib")
find_library(absl_civil_time_LIBRARY absl_civil_time PATHS "${OR_TOOLS_ROOT}/lib")
find_library(absl_debugging_internal_LIBRARY absl_debugging_internal PATHS "${OR_TOOLS_ROOT}/lib")
find_library(absl_demangle_internal_LIBRARY absl_demangle_internal PATHS "${OR_TOOLS_ROOT}/lib")
find_library(absl_dynamic_annotations_LIBRARY absl_dynamic_annotations PATHS "${OR_TOOLS_ROOT}/lib")
find_library(absl_examine_stack_LIBRARY absl_examine_stack PATHS "${OR_TOOLS_ROOT}/lib")
find_library(absl_failure_signal_handler_LIBRARY absl_failure_signal_handler PATHS "${OR_TOOLS_ROOT}/lib")
find_library(absl_graphcycles_internal_LIBRARY absl_graphcycles_internal PATHS "${OR_TOOLS_ROOT}/lib")
find_library(absl_hash_LIBRARY absl_hash PATHS "${OR_TOOLS_ROOT}/lib")
find_library(absl_hashtablez_sampler_LIBRARY absl_hashtablez_sampler PATHS "${OR_TOOLS_ROOT}/lib")
find_library(absl_int128_LIBRARY absl_int128 PATHS "${OR_TOOLS_ROOT}/lib")
find_library(absl_leak_check_LIBRARY absl_leak_check PATHS "${OR_TOOLS_ROOT}/lib")
find_library(absl_malloc_internal_LIBRARY absl_malloc_internal PATHS "${OR_TOOLS_ROOT}/lib")
find_library(absl_optional_LIBRARY absl_optional PATHS "${OR_TOOLS_ROOT}/lib")
find_library(absl_raw_hash_set_LIBRARY absl_raw_hash_set PATHS "${OR_TOOLS_ROOT}/lib")
find_library(absl_spinlock_wait_LIBRARY absl_spinlock_wait PATHS "${OR_TOOLS_ROOT}/lib")
find_library(absl_stacktrace_LIBRARY absl_stacktrace PATHS "${OR_TOOLS_ROOT}/lib")
find_library(absl_str_format_internal_LIBRARY absl_str_format_internal PATHS "${OR_TOOLS_ROOT}/lib")
find_library(absl_strings_internal_LIBRARY absl_strings_internal PATHS "${OR_TOOLS_ROOT}/lib")
find_library(absl_strings_LIBRARY absl_strings PATHS "${OR_TOOLS_ROOT}/lib")
find_library(absl_symbolize_LIBRARY absl_symbolize PATHS "${OR_TOOLS_ROOT}/lib")
find_library(absl_synchronization_LIBRARY absl_synchronization PATHS "${OR_TOOLS_ROOT}/lib")
find_library(absl_throw_delegate_LIBRARY absl_throw_delegate PATHS "${OR_TOOLS_ROOT}/lib")
find_library(absl_time_zone_LIBRARY absl_time_zone PATHS "${OR_TOOLS_ROOT}/lib")
find_library(absl_time_LIBRARY absl_time PATHS "${OR_TOOLS_ROOT}/lib")

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
    ortools_LIBRARY
    absl_bad_any_cast_impl_LIBRARY
    absl_bad_optional_access_LIBRARY
    absl_bad_variant_access_LIBRARY
    absl_base_LIBRARY
    absl_city_LIBRARY
    absl_civil_time_LIBRARY
    absl_debugging_internal_LIBRARY
    absl_demangle_internal_LIBRARY
    absl_dynamic_annotations_LIBRARY
    absl_examine_stack_LIBRARY
    absl_failure_signal_handler_LIBRARY
    absl_graphcycles_internal_LIBRARY
    absl_hash_LIBRARY
    absl_hashtablez_sampler_LIBRARY
    absl_int128_LIBRARY
    absl_leak_check_LIBRARY
    absl_malloc_internal_LIBRARY
    absl_optional_LIBRARY
    absl_raw_hash_set_LIBRARY
    absl_spinlock_wait_LIBRARY
    absl_stacktrace_LIBRARY
    absl_str_format_internal_LIBRARY
    absl_strings_internal_LIBRARY
    absl_strings_LIBRARY
    absl_symbolize_LIBRARY
    absl_synchronization_LIBRARY
    absl_throw_delegate_LIBRARY
    absl_time_zone_LIBRARY
    absl_time_LIBRARY)

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
    ${ortools_LIBRARY}
    ${absl_bad_any_cast_impl_LIBRARY}
    ${absl_bad_optional_access_LIBRARY}
    ${absl_bad_variant_access_LIBRARY}
    ${absl_base_LIBRARY}
    ${absl_city_LIBRARY}
    ${absl_civil_time_LIBRARY}
    ${absl_debugging_internal_LIBRARY}
    ${absl_demangle_internal_LIBRARY}
    ${absl_dynamic_annotations_LIBRARY}
    ${absl_examine_stack_LIBRARY}
    ${absl_failure_signal_handler_LIBRARY}
    ${absl_graphcycles_internal_LIBRARY}
    ${absl_hash_LIBRARY}
    ${absl_hashtablez_sampler_LIBRARY}
    ${absl_int128_LIBRARY}
    ${absl_leak_check_LIBRARY}
    ${absl_malloc_internal_LIBRARY}
    ${absl_optional_LIBRARY}
    ${absl_raw_hash_set_LIBRARY}
    ${absl_spinlock_wait_LIBRARY}
    ${absl_stacktrace_LIBRARY}
    ${absl_str_format_internal_LIBRARY}
    ${absl_strings_internal_LIBRARY}
    ${absl_strings_LIBRARY}
    ${absl_symbolize_LIBRARY}
    ${absl_synchronization_LIBRARY}
    ${absl_throw_delegate_LIBRARY}
    ${absl_time_zone_LIBRARY}
    ${absl_time_LIBRARY})
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
    ortools_LIBRARY
    absl_bad_any_cast_impl_LIBRARY
    absl_bad_optional_access_LIBRARY
    absl_bad_variant_access_LIBRARY
    absl_base_LIBRARY
    absl_city_LIBRARY
    absl_civil_time_LIBRARY
    absl_debugging_internal_LIBRARY
    absl_demangle_internal_LIBRARY
    absl_dynamic_annotations_LIBRARY
    absl_examine_stack_LIBRARY
    absl_failure_signal_handler_LIBRARY
    absl_graphcycles_internal_LIBRARY
    absl_hash_LIBRARY
    absl_hashtablez_sampler_LIBRARY
    absl_int128_LIBRARY
    absl_leak_check_LIBRARY
    absl_malloc_internal_LIBRARY
    absl_optional_LIBRARY
    absl_raw_hash_set_LIBRARY
    absl_spinlock_wait_LIBRARY
    absl_stacktrace_LIBRARY
    absl_str_format_internal_LIBRARY
    absl_strings_internal_LIBRARY
    absl_strings_LIBRARY
    absl_symbolize_LIBRARY
    absl_synchronization_LIBRARY
    absl_throw_delegate_LIBRARY
    absl_time_zone_LIBRARY
    absl_time_LIBRARY)
