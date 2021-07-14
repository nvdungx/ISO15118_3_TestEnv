
find_path(gpiod_INCLUDE_DIR gpiod.h)
unset(gpiod_LIBRARY CACHE)
find_library(gpiod_LIBRARY gpiod)
mark_as_advanced(gpiod_INCLUDE_DIR gpiod_LIBRARY)

# Handle the REQUIRED argument and set gpiod_FOUND
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(gpiod DEFAULT_MSG gpiod_LIBRARY gpiod_INCLUDE_DIR)

if(gpiod_FOUND AND NOT TARGET gpiod::gpiod)
  add_library(gpiod::gpiod UNKNOWN IMPORTED)
  set_target_properties(gpiod::gpiod PROPERTIES
    IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
    IMPORTED_LOCATION "${gpiod_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES "${gpiod_INCLUDE_DIR}"
  )
  target_link_options(gpiod::gpiod INTERFACE libgpiod)
  message(STATUS "lib: ${gpiod_LIBRARY}
                  dir: ${gpiod_INCLUDE_DIR}")
endif()
