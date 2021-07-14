# Try to find UUID library and include path.
# Once done this will define
#
# UUID_FOUND
# UUID_INCLUDE_DIR
# UUID_LIBRARIES

find_path(UUID_INCLUDE_DIR uuid/uuid.h)
find_library(UUID_LIBRARY uuid)

# Handle the REQUIRED argument and set UUID_FOUND
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(UUID DEFAULT_MSG UUID_LIBRARY UUID_INCLUDE_DIR)

mark_as_advanced(UUID_INCLUDE_DIR)
mark_as_advanced(UUID_LIBRARY)

if(UUID_FOUND)
  message(STATUS "Found UUID library")
  add_definitions(-DUUID_SUPPORT)
  set(UUID_LIBRARIES ${UUID_LIBRARY})
endif()
