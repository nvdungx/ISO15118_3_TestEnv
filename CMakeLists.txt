cmake_minimum_required(VERSION 3.0.0)
project(slac LANGUAGES C CXX VERSION 0.1.0)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Compiler features
include(SetCompilerFeatures)
include(SetCompilerWarnings)
include(SetPlatformFeatures)
include(SystemInformation)

# External packages
# find_package(OpenSSL REQUIRED)
# if (${OPENSSL_FOUND})
#   message(STATUS "libssl-dev version: ${OPENSSL_VERSION} | ${OPENSSL_LIBRARIES} | ${OPENSSL_INCLUDE_DIR}")
#   list(APPEND GLB_LINK_LIBS ${OPENSSL_LIBRARIES})
# else ()
#   message(STATUS "libssl-dev not found")
# endif()

# find_package(Threads REQUIRED)
# list(APPEND GLB_LINK_LIBS Threads)

# find_package(Protobuf REQUIRED)
# if (${PROTOBUF_FOUND})
#   message(STATUS "Protobuf-dev version: ${PROTOBUF_VERSION} | ${PROTOBUF_LIBRARIES} | ${PROTOBUF_INCLUDE_DIR}")
#   list(APPEND GLB_LINK_LIBS ${PROTOBUF_LIBRARIES})
# else ()
#   message(STATUS "Protobuf-dev not found")
# endif()

# set(Boost_DEBUG 1)
find_package(Boost REQUIRED)
if (Boost_FOUND)
  message(STATUS "Boost-dev version: ${Boost_VERSION} | ${Boost_LIBRARIES} | ${Boost_INCLUDE_DIR}")
else ()
  message(STATUS "Boost-dev not found")
endif()

add_subdirectory(libs)
list(APPEND GLB_LINK_LIBS spdlog::spdlog)
message(STATUS "GLOBAL LINK LIBS: ${GLB_LINK_LIBS}")

set_property(GLOBAL PROPERTY glb_ext_libs "${GLB_LINK_LIBS}")

add_subdirectory(modules)

# file(GLOB_RECURSE src_files LIST_DIRECTORIES false CONFIGURE_DEPENDS "src/*.cpp")
list(APPEND src_files ${CMAKE_CURRENT_SOURCE_DIR}/test/main.cpp)

add_executable(main ${src_files})
target_link_libraries(main PUBLIC ${GLB_LINK_LIBS}
                          PRIVATE lib_basic_signaling_if lib_datatype lib_codecs
                          lib_platform_if lib_plc_if lib_runtime_if)

target_include_directories(main PUBLIC "./include")

include(CTest)
enable_testing()


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
