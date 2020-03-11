cmake_minimum_required(VERSION 3.2)

project(commons)

set(SOURCE_FILES
    cond_var.cpp
    iexchange_data.cpp
    ithread.cpp
)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} -lpthread)
