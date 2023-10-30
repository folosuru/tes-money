cmake_minimum_required(VERSION 3.21)
set(project_name_ tes-bank)
project(${project_name_})

file(GLOB_RECURSE SRC_MONEY_DIR
		${${project_name_}_SOURCE_DIR}/src/*.c
		${${project_name_}_SOURCE_DIR}/src/*.cpp
		${${project_name_}_SOURCE_DIR}/src/*.h
		${${project_name_}_SOURCE_DIR}/src/*.hpp
)

add_library(${project_name_} SHARED ${SRC_MONEY_DIR})

LiteLoader_options(${project_name_})
LiteLoader_include(${project_name_})
LiteLoader_libraries(${project_name_})

target_include_directories(${project_name_} PRIVATE
		${${project_name_}_SOURCE_DIR}/header/
		${${project_name_}_SOURCE_DIR}/../money/header
)

add_subdirectory(test)
