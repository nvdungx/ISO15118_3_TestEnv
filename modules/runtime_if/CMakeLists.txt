project(lib_runtime_if VERSION 1.0.0)

message("-- Lib identification: ${PROJECT_NAME} | src:${PROJECT_SOURCE_DIR} | out:${PROJECT_BINARY_DIR}")

file(GLOB_RECURSE src_files LIST_DIRECTORIES false CONFIGURE_DEPENDS "src/*.cpp" "include/*.hpp")

add_library(lib_runtime_if OBJECT ${src_files})

get_property(GBL_LINK_LIBS GLOBAL PROPERTY glb_ext_libs)

target_link_libraries(lib_runtime_if PUBLIC ${GBL_LINK_LIBS} lib_datatype)

target_include_directories(lib_runtime_if PUBLIC "./include")

# enable asio tracking
# target_compile_definitions(lib_runtime_if PUBLIC BOOST_ASIO_ENABLE_HANDLER_TRACKING)

# test module
add_executable(test_runtime_if ./test/test.cpp)

target_link_libraries(test_runtime_if PUBLIC lib_runtime_if)