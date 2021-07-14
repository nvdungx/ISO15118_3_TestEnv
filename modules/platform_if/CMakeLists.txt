project(lib_platform_if VERSION 1.0.0)

message("-- Lib identification: ${PROJECT_NAME} | src:${PROJECT_SOURCE_DIR} | out:${PROJECT_BINARY_DIR}")

file(GLOB_RECURSE src_files LIST_DIRECTORIES false CONFIGURE_DEPENDS "*.cpp")

add_library(lib_platform_if OBJECT ${src_files})

target_link_libraries(lib_platform_if PRIVATE spdlog::spdlog)
target_include_directories(lib_platform_if PUBLIC "./include")