set(project_name_ tes-util-test)
project(${project_name_})
file(GLOB_RECURSE files

)
add_definitions(
        -D DEBUG_WITHOUT_LLAPI
        -D TEST
        -D AsyncTask_NOT_USE_DLL
)
add_link_options(
    /DEBUG
)
add_executable(${project_name_} test.cpp ${files})
LiteLoader_include(${project_name_})
target_include_directories(${project_name_} PRIVATE
        ${${project_name_}_SOURCE_DIR}/../../header/
        ${${project_name_}_SOURCE_DIR}/../../lib/cpptf/
)