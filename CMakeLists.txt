cmake_minimum_required(VERSION 3.8)
project(CatchTests)

set(CMAKE_CXX_STANDARD 17)
include_directories(lib)

add_subdirectory(code)
add_subdirectory(tests)


