set(project_name_ tes-money-test)
project(${project_name_})
file(GLOB_RECURSE files
        ${${project_name_}_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/../src/*/*.cpp
        ${PROJECT_SOURCE_DIR}/../src/*/*.hpp
)
add_definitions(
        -D DEBUG_WITHOUT_LLAPI
        -D TEST
)
add_link_options(
    /DEBUG
)
add_executable(${project_name_} test.cpp ${files})
LiteLoader_include(${project_name_})
target_include_directories(${project_name_} PRIVATE
        ${${project_name_}_SOURCE_DIR}/../header/
        ${${project_name_}_SOURCE_DIR}/../../cpptf/
)