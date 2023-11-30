cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_BUILD_TYPE Release)
include(LiteLoaderBDS.cmake)
add_compile_options(
        /utf-8
)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(project_name_ tes)
project(${project_name_})
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/artifact)
add_subdirectory(lib)
include_thirdparty_libraries()
include_directories(util)
cmake_minimum_required(VERSION 3.21)

file(GLOB_RECURSE SRC_MONEY_DIR
        ${CMAKE_SOURCE_DIR}/src/*.c
        ${CMAKE_SOURCE_DIR}/src/*.cpp
        ${CMAKE_SOURCE_DIR}/src/*.h
        ${CMAKE_SOURCE_DIR}/src/*.hpp
        )

add_library(${project_name_} SHARED ${SRC_MONEY_DIR})

LiteLoader_options(${project_name_})
LiteLoader_include(${project_name_})
LiteLoader_libraries(${project_name_})
target_link_libraries(${project_name_}
        AsyncTask
        SQLiteCpp
        sqlite3
        CppArrai18n
        )
target_include_directories(${project_name_} PRIVATE
        ${CMAKE_SOURCE_DIR}/header/
        )

add_subdirectory(test)