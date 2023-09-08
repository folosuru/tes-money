cmake_minimum_required(VERSION 3.21)

project(tester)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Release)

include_directories(
        ${CMAKE_SOURCE_DIR}/../SDK/include
        ${CMAKE_SOURCE_DIR}/../money/header
)
file(GLOB_RECURSE TES_FILES_DIR
        ${PROJECT_SOURCE_DIR}/../money/src/*/*.cpp
        ${PROJECT_SOURCE_DIR}/../money/src/*/*.hpp
)
message(${TES_FILES_DIR})
add_definitions(
        -D"_AMD64_"
        -D DEBUG_WITHOUT_LLAPI
)
add_compile_options(
        /utf-8
        /D TEST
)

add_executable(tester ${TES_FILES_DIR} "${CMAKE_SOURCE_DIR}/test.cpp")
