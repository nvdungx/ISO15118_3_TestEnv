project(lib_platform_if VERSION 1.0.0)

message("-- Lib identification: ${PROJECT_NAME} | src:${PROJECT_SOURCE_DIR} | out:${PROJECT_BINARY_DIR}")

file(GLOB_RECURSE src_files LIST_DIRECTORIES false CONFIGURE_DEPENDS "src/*.cpp" "include/*.hpp")

add_library(lib_platform_if OBJECT ${src_files})

get_property(GBL_LINK_LIBS GLOBAL PROPERTY glb_ext_libs)

target_link_libraries(lib_platform_if PUBLIC ${GBL_LINK_LIBS} lib_datatype)

target_include_directories(lib_platform_if PUBLIC "./include")

# test module
add_executable(test_platform_adp ./test/test.cpp)

target_link_libraries(test_platform_adp PUBLIC lib_platform_if)