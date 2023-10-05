set(project_name_ tes-util-test)
set(CMAKE_CXX_STANDARD 17)
project(${project_name_})
add_definitions(
        -D DEBUG_WITHOUT_LLAPI
        -D TEST
)
add_link_options(
    /DEBUG
)
add_executable(${project_name_} test.cpp ${files})
target_include_directories(${project_name_} PRIVATE
        ${${project_name_}_SOURCE_DIR}/../../
        ${${project_name_}_SOURCE_DIR}/../../cpptf/
)
