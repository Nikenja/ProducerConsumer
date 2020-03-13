cmake_minimum_required(VERSION 3.2)

project(exchange_data)

add_definitions(-DFDEBUG)

add_subdirectory(commons)
add_subdirectory(protocols/autots)
add_subdirectory(tests)

add_executable(${PROJECT_NAME} main.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

target_link_libraries(${PROJECT_NAME} PRIVATE commons autots)

