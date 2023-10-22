cmake_minimum_required(VERSION 3.21)
set(project_name_ tes-country)
set(CMAKE_CXX_STANDARD 20)
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


target_link_libraries(${project_name_} 
	"${${project_name_}_SOURCE_DIR}/../SDK/lib/LiteLoader.lib"
	"${${project_name_}_SOURCE_DIR}/../SDK/lib/bedrock_server_api.lib"
	"${${project_name_}_SOURCE_DIR}/../SDK/lib/bedrock_server_var.lib"
	"${${project_name_}_SOURCE_DIR}/../SDK/lib/SymDBHelper.lib"
	SQLiteCpp
	sqlite3
)
target_include_directories(${project_name_} PRIVATE
		${${project_name_}_SOURCE_DIR}/header/country/
		${${project_name_}_SOURCE_DIR}/../money/header/
)

target_link_directories(${project_name_}
	PRIVATE ${${project_name_}_SOURCE_DIR}/../SDK/lib
)
add_custom_command(TARGET ${project_name_} PRE_BUILD
    COMMAND cmd /c ${${project_name_}_SOURCE_DIR}/../prepare_libraries.cmd ${${project_name_}_SOURCE_DIR}/../
)

add_subdirectory(test)