set(project_name_ tes-country-test)
project(${project_name_})
set(CMAKE_CXX_STANDARD 20)
file(GLOB_RECURSE files
        ${${project_name_}_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/src/country/*.cpp
        ${CMAKE_SOURCE_DIR}/src/country/*.hpp
        ${CMAKE_SOURCE_DIR}/src/misc/*.cpp
        ${CMAKE_SOURCE_DIR}/src/money/*.cpp
        ${CMAKE_SOURCE_DIR}/src/money/*.hpp

)
add_definitions(
        -D DEBUG_WITHOUT_LLAPI
        -D TEST
        -D AsyncTask_NOT_USE_DLL
)
add_link_options(
    /DEBUG
)
add_executable(${project_name_}
    test.cpp
    ${files}
    ${CMAKE_SOURCE_DIR}/lib/AsyncTask/mock/TaskManagerMock.cpp)

#find_package(libpqxx CONFIG REQUIRED)
#target_link_libraries(${project_name_} libpqxx::pqxx)
LiteLoader_include(${project_name_})
target_link_libraries(${project_name_}
        SQLiteCpp
        sqlite3
)
target_include_directories(${project_name_} PRIVATE
        ${CMAKE_SOURCE_DIR}/header/
)