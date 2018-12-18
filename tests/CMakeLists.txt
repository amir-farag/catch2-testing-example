cmake_minimum_required(VERSION 3.8)
project(Tests)
set(CMAKE_CXX_STANDARD 17)

SET(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage -g -O0")
SET(GCC_COVERAGE_LINK_FLAGS    "--coverage")

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

set(SOURCE_FILES
        main_tests.cpp
        ../code/Receiver.cpp ../code/Receiver.h ../code/Sender.cpp ../code/Sender.h)
add_executable(Tests ${SOURCE_FILES} )