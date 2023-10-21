set(project_name_ tes-country-test)
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

find_package(libpqxx CONFIG REQUIRED)
target_link_libraries(${project_name_} libpqxx::pqxx)
LiteLoader_libraries(${project_name_})
LiteLoader_include(${project_name_})
target_link_libraries(${project_name_}
        SQLiteCpp
        sqlite3
)
target_include_directories(${project_name_} PRIVATE
        ${${project_name_}_SOURCE_DIR}/../header/country/
        ${${project_name_}_SOURCE_DIR}/../../
        ${${project_name_}_SOURCE_DIR}/../../cpptf/
)