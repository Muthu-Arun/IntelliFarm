cmake_minimum_required(VERSION 3.10)

# Set your project name
project(server)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories for header files
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/vendor/crow
    ${CMAKE_SOURCE_DIR}/vendor/sqlite3
)

# Add the executable and specify the source files
add_executable(${PROJECT_NAME}
    ./src/main.cpp
    ./src/dbms.cpp
    ./src/rab.cpp
    ./vendor/sqlite3/sqlite3.c
)

# Add any additional libraries if required
# target_link_libraries(${PROJECT_NAME} <library_name>)

