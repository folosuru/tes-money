function(LiteLoader_options project_name)
    target_compile_definitions( ${project_name}
        PRIVATE -D"NDEBUG"
        PRIVATE -D"NOMINMAX"
        PRIVATE -D"TEMPLATE_EXPORTS"
        PRIVATE -D"UNICODE"
        PRIVATE -D"WIN32_LEAN_AND_MEAN"
        PRIVATE -D"_AMD64_"
        PRIVATE -D"_CRT_SECURE_NO_WARNINGS"
        PRIVATE -D"_UNICODE"
        PRIVATE -D"_USRDLL"
        PRIVATE -D"_WINDLL"
        PRIVATE -D"_WINDOWS"
    )

    target_compile_options(${project_name}
        PRIVATE /diagnostics:column
        PRIVATE /EHsc
        PRIVATE /FC
        PRIVATE /GL
        PRIVATE /MD
        PRIVATE /nologo
        PRIVATE /permissive-
        PRIVATE /sdl
        PRIVATE /utf-8
        PRIVATE /Zc:inline
        PRIVATE /Zi
    )

    target_link_options(${project_name}
        PRIVATE /DEBUG
        PRIVATE /DELAYLOAD:"bedrock_server.dll"
        PRIVATE /DLL
        PRIVATE /IGNORE:4199
        PRIVATE /INCREMENTAL:NO
        PRIVATE /LTCG:INCREMENTAL
        PRIVATE /MANIFESTUAC:NO
        PRIVATE /MACHINE:X64
        PRIVATE /NOLOGO
        PRIVATE /OPT:ICF
        PRIVATE /OPT:REF
        PRIVATE /SUBSYSTEM:CONSOLE
    )
endfunction()

function(LiteLoader_include project_name)
    target_include_directories(${project_name} PRIVATE
        ${CMAKE_SOURCE_DIR}/SDK/include
    )
endfunction()

function(LiteLoader_libraries project_name)
    target_link_libraries(${project_name}
        "${CMAKE_SOURCE_DIR}/SDK/lib/LiteLoader.lib/SDK/lib/LiteLoader.lib"
        "${CMAKE_SOURCE_DIR}/SDK/lib/LiteLoader.lib/SDK/lib/bedrock_server_api.lib"
        "${CMAKE_SOURCE_DIR}/SDK/lib/LiteLoader.lib/SDK/lib/bedrock_server_var.lib"
        "${CMAKE_SOURCE_DIR}/SDK/lib/LiteLoader.lib/SDK/lib/SymDBHelper.lib"
    )
    target_link_directories(${project_name}
        PRIVATE ${CMAKE_SOURCE_DIR}/SDK/lib
    )
    add_custom_command(TARGET ${project_name} PRE_BUILD
        COMMAND cmd /c ${CMAKE_SOURCE_DIR}/prepare_libraries.cmd ${CMAKE_SOURCE_DIR}/
    )
endfunction()