function(LiteLoader_options)
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
endfunction()
function(LiteLoader_libraries project_name)
    target_link_libraries(${project_name}
        "${CMAKE_SOURCE_DIR}/SDK/lib/LiteLoader.lib/SDK/lib/LiteLoader.lib"
        "${CMAKE_SOURCE_DIR}/SDK/lib/LiteLoader.lib/SDK/lib/bedrock_server_api.lib"
        "${CMAKE_SOURCE_DIR}/SDK/lib/LiteLoader.lib/SDK/lib/bedrock_server_var.lib"
        "${CMAKE_SOURCE_DIR}/SDK/lib/LiteLoader.lib/SDK/lib/SymDBHelper.lib"
    )
    target_include_directories(${project_name} PRIVATE
        ${CMAKE_SOURCE_DIR}/SDK/include
    )
    target_link_directories(${project_name}
        PRIVATE ${CMAKE_SOURCE_DIR}/SDK/lib
    )
    add_custom_command(TARGET ${project_name} PRE_BUILD
        COMMAND cmd /c ${CMAKE_SOURCE_DIR}/prepare_libraries.cmd ${CMAKE_SOURCE_DIR}/
    )
endfunction()