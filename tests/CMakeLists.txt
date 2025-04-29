cmake_minimum_required(VERSION 3.20.10)

project(test)

add_executable(test_dbms ./src/dbms.test.cpp
   ./../src/dbms.cpp
)
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../src
    ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/mysqlx
)

target_link_libraries(test_dbms STATIC mysqlcppconnx)
