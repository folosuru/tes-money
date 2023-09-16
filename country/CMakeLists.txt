cmake_minimum_required(VERSION 3.21)
set(project_name tes-country)
project(${project_name})

file(GLOB_RECURSE SRC_MONEY_DIR
		${${project_name}_SOURCE_DIR}/src/*.c
		${${project_name}_SOURCE_DIR}/src/*.cpp
		${${project_name}_SOURCE_DIR}/src/*.h
		${${project_name}_SOURCE_DIR}/src/*.hpp
)

add_definitions(
    -D"NDEBUG"
    -D"NOMINMAX"
    -D"TEMPLATE_EXPORTS"
    -D"UNICODE"
    -D"WIN32_LEAN_AND_MEAN"
    -D"_AMD64_"
    -D"_CRT_SECURE_NO_WARNINGS"
    -D"_UNICODE"
    -D"_USRDLL"
    -D"_WINDLL"
    -D"_WINDOWS"
)

add_compile_options(
    /diagnostics:column
    /EHsc
    /FC
    /GL
    /MD
    /nologo
    /permissive-
    /sdl
    /utf-8
    /Zc:inline
    /Zi
)

add_link_options(
    /DEBUG
    /DELAYLOAD:"bedrock_server.dll"
    /DLL
    /IGNORE:4199
    /INCREMENTAL:NO
    /LTCG:INCREMENTAL
    /MANIFESTUAC:NO
    /MACHINE:X64
    /NOLOGO
    /OPT:ICF
    /OPT:REF
    /SUBSYSTEM:CONSOLE
)

add_library(${project_name} SHARED ${SRC_MONEY_DIR})

target_link_libraries(${project_name} 
	"${${project_name}_SOURCE_DIR}/../SDK/lib/LiteLoader.lib"
	"${${project_name}_SOURCE_DIR}/../SDK/lib/bedrock_server_api.lib"
	"${${project_name}_SOURCE_DIR}/../SDK/lib/bedrock_server_var.lib"
	"${${project_name}_SOURCE_DIR}/../SDK/lib/SymDBHelper.lib"
)
target_include_directories(${project_name} PRIVATE
		${${project_name}_SOURCE_DIR}/../SDK/include
		${${project_name}_SOURCE_DIR}/header/
		${${project_name}_SOURCE_DIR}/../money/header/
)

target_link_directories(${project_name}
	PRIVATE ${${project_name}_SOURCE_DIR}/../SDK/lib
)

add_custom_command(TARGET ${project_name} PRE_BUILD
    COMMAND cmd /c ${${project_name}_SOURCE_DIR}/../prepare_libraries.cmd ${${project_name}_SOURCE_DIR}/../
)
