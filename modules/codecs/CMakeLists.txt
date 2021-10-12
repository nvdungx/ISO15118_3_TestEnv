project(lib_codecs VERSION 1.0.0)

message("-- Lib identification: ${PROJECT_NAME} | src:${PROJECT_SOURCE_DIR} | out:${PROJECT_BINARY_DIR}")

file(GLOB_RECURSE src_files LIST_DIRECTORIES false CONFIGURE_DEPENDS "src/*.cpp" "include/*.hpp")

add_library(lib_codecs OBJECT ${src_files})

get_property(GBL_LINK_LIBS GLOBAL PROPERTY glb_ext_libs)

target_link_libraries(lib_codecs PUBLIC ${GBL_LINK_LIBS} lib_datatype)

target_include_directories(lib_codecs PUBLIC "./include")

# test module
add_executable(test_codecs ./test/test.cpp)

target_link_libraries(test_codecs PUBLIC lib_codecs)