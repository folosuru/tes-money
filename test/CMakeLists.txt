cmake_minimum_required(VERSION 3.21)

project(tester)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Release)

include_directories(
        ${CMAKE_SOURCE_DIR}/../SDK/include
)
file(GLOB_RECURSE TES_FILES_DIR
        ${PROJECT_SOURCE_DIR}/../src/*/*.c
        ${PROJECT_SOURCE_DIR}/../src/*/*.cpp
        ${PROJECT_SOURCE_DIR}/../src/*/*.h
        ${PROJECT_SOURCE_DIR}/../src/*/*.hpp
        )

add_compile_options(
        /utf-8
)
add_executable(tester ${TES_FILES_DIR} "${CMAKE_SOURCE_DIR}/test.cpp")
