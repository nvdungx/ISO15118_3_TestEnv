project(lib_basic_signaling_if VERSION 1.0.0)

find_package(pigpiodif REQUIRED)

message("-- Lib identification: ${PROJECT_NAME} | src:${PROJECT_SOURCE_DIR} | out:${PROJECT_BINARY_DIR}")

file(GLOB_RECURSE src_files LIST_DIRECTORIES false CONFIGURE_DEPENDS "src/*.cpp" "include/*.hpp")

# message(${src_files})

add_library(lib_basic_signaling_if OBJECT ${src_files})

get_property(GBL_LINK_LIBS GLOBAL PROPERTY glb_ext_libs)

target_link_libraries(lib_basic_signaling_if PRIVATE pigpiodif::pigpiodif
                                            PUBLIC ${GBL_LINK_LIBS} lib_datatype)
target_include_directories(lib_basic_signaling_if PUBLIC "./include")

# test module
add_executable(test_basic_signaling ./test/test.cpp)

target_link_libraries(test_basic_signaling PUBLIC lib_basic_signaling_if)