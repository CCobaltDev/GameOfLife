cmake_minimum_required(VERSION 3.20)
project(GameOfLife LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(GLFW_BUILD_WAYLAND ON CACHE BOOL "")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out)

add_subdirectory(thirdparty/raylib)

add_executable(${PROJECT_NAME} src/main.cpp src/GameOfLife.cpp src/GameOfLife.h)
target_include_directories(${PROJECT_NAME} PRIVATE src)
target_link_libraries(${PROJECT_NAME} raylib)