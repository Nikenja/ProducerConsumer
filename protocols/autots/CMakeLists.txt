cmake_minimum_required(VERSION 3.2)

project(autots)

add_library(${PROJECT_NAME} SHARED autots_routine.cpp)

target_link_libraries(${PROJECT_NAME} commons)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
