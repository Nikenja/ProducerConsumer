project(thread)

set(SOURCE_FILES
    cond_var.cpp
    ithread.cpp
    iroutine.cpp
    thread_defs.cpp
    thread_joining_data.cpp
    thread_join_timeout.cpp
    isignal_handler.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} -lpthread logger thread_safe)

add_subdirectory(test)
