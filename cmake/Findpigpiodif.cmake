
find_path(pigpiodif_INCLUDE_DIR pigpiod_if2.h)
unset(pigpiodif_LIBRARY CACHE)
find_library(pigpiodif_LIBRARY pigpiod_if2)
mark_as_advanced(pigpiodif_INCLUDE_DIR pigpiodif_LIBRARY)

# Handle the REQUIRED argument and set pigpiodif_FOUND
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(pigpiodif DEFAULT_MSG pigpiodif_LIBRARY pigpiodif_INCLUDE_DIR)

if(pigpiodif_FOUND AND NOT TARGET pigpiodif::pigpiodif)
  add_library(pigpiodif::pigpiodif UNKNOWN IMPORTED)
  set_target_properties(pigpiodif::pigpiodif PROPERTIES
    IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
    IMPORTED_LOCATION "${pigpiodif_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES "${pigpiodif_INCLUDE_DIR}"
  )
  target_link_options(pigpiodif::pigpiodif INTERFACE libpigpiodif)
  message(STATUS "lib: ${pigpiodif_LIBRARY}
                  dir: ${pigpiodif_INCLUDE_DIR}")
endif()
