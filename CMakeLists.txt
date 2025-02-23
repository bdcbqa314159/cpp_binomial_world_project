cmake_minimum_required(VERSION 3.30)

project(cpp_binomial_world_project LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

MESSAGE(STATUS "the source directory is: ${CMAKE_SOURCE_DIR}")

add_subdirectory(code)



