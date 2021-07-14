# Try to find RT library and include path.
# Once done this will define
#
# Rt_FOUND
# Rt_INCLUDE_DIR
# Rt_LIBRARIES

find_path(Rt_INCLUDE_DIR time.h)
find_library(Rt_LIBRARY rt)
mark_as_advanced(Rt_INCLUDE_DIR Rt_LIBRARY)

# Handle the REQUIRED argument and set Rt_FOUND
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Rt REQUIRED_VARS DEFAULT_MSG Rt_LIBRARY Rt_INCLUDE_DIR)

if(Rt_FOUND AND NOT TARGET Rt::Rt)
  add_library(Rt::Rt UNKNOWN IMPORTED)
  set_target_properties(Rt::Rt PROPERTIES
    IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
    IMPORTED_LOCATION "${Rt_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES "${Rt_INCLUDE_DIR}"
  )
endif()
