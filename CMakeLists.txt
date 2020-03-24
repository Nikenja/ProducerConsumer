cmake_minimum_required(VERSION 3.2)

project(main)

add_definitions(-DFDEBUG)

enable_testing()

add_subdirectory(commons)

add_executable(${PROJECT_NAME} main.cpp)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)

target_link_libraries(${PROJECT_NAME} PRIVATE exchange_data)
