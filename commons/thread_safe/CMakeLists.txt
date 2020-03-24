project(thread_safe)

set(SOURCE_FILES
    safe_state.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} -lpthread)
