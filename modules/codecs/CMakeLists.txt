project(lib_codecs VERSION 1.0.0)

message("-- Lib identification: ${PROJECT_NAME} | src:${PROJECT_SOURCE_DIR} | out:${PROJECT_BINARY_DIR}")

file(GLOB_RECURSE src_files LIST_DIRECTORIES false CONFIGURE_DEPENDS "*.cpp")

add_library(lib_codecs OBJECT ${src_files})

target_link_libraries(lib_codecs PRIVATE spdlog::spdlog)
target_include_directories(lib_codecs PUBLIC "./include")