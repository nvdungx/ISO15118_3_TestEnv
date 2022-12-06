project(lib_execution VERSION 1.0.0)

message("-- Lib identification: ${PROJECT_NAME} | src:${PROJECT_SOURCE_DIR} | out:${PROJECT_BINARY_DIR}")

file(GLOB_RECURSE src_files LIST_DIRECTORIES false CONFIGURE_DEPENDS "src/*.cpp" "include/*.hpp")

# message(${src_files})

add_library(lib_execution OBJECT ${src_files})

get_property(GBL_LINK_LIBS GLOBAL PROPERTY glb_ext_libs)

target_link_libraries(lib_execution PUBLIC ${GBL_LINK_LIBS} lib_datatype lib_runtime_if lib_codecs)
target_include_directories(lib_execution PUBLIC "./include")

# test module
add_executable(test_execution ./test/test.cpp)

target_link_libraries(test_execution PUBLIC lib_execution)