cmake_minimum_required(VERSION 3.2)

project(commons)

set(SOURCE_FILES
    cond_var.cpp
    iexchange_data.cpp
    ithread.cpp
    safe_state.cpp
    iroutine.cpp
    consumer_routine.cpp
    waiting_time_getter.cpp
    pthread_join_timeout.cpp
)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} -lpthread)
