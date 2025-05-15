cmake_minimum_required(VERSION 3.10.0)
project(GAME VERSION 0.1.0 LANGUAGES C CXX)

file(GLOB_RECURSE MY_SOURCES CONFIG_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.cpp")
 
add_subdirectory("${CMAKE_SOURCE_DIR}\\third_party\\raylib")
add_subdirectory("${CMAKE_SOURCE_DIR}\\third_party\\imgui-docking")
add_subdirectory("${CMAKE_SOURCE_DIR}\\third_party\\rlImGui")

add_executable(GAME "${MY_SOURCES}")

target_include_directories(GAME PRIVATE "${CMAKE_SOURCE_DIR}/include/")
target_compile_definitions(GAME PUBLIC RESOURCE_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")
target_link_libraries(GAME raylib imgui rlimgui)
