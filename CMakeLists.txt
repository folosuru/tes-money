cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Release)
include(LiteLoaderBDS.cmake)
add_compile_options(
        /utf-8
)
project(tes)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/artifact)
add_subdirectory(money)
add_subdirectory(country)
