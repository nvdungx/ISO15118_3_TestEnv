
find_path(gpiodcxx_INCLUDE_DIR gpiod.hpp)
unset(gpiodcxx_LIBRARY CACHE)
find_library(gpiodcxx_LIBRARY gpiodcxx)
mark_as_advanced(gpiodcxx_INCLUDE_DIR gpiodcxx_LIBRARY)

# Handle the REQUIRED argument and set gpiodcxx_FOUND
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(gpiodcxx DEFAULT_MSG gpiodcxx_LIBRARY gpiodcxx_INCLUDE_DIR)

if(gpiodcxx_FOUND AND NOT TARGET gpiodcxx::gpiodcxx)
  add_library(gpiodcxx::gpiodcxx UNKNOWN IMPORTED)
  set_target_properties(gpiodcxx::gpiodcxx PROPERTIES
    IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
    IMPORTED_LOCATION "${gpiodcxx_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES "${gpiodcxx_INCLUDE_DIR}"
  )
  target_link_options(gpiodcxx::gpiodcxx INTERFACE libgpiodcxx)
  message(STATUS "lib: ${gpiodcxx_LIBRARY}
                  dir: ${gpiodcxx_INCLUDE_DIR}")
endif()
