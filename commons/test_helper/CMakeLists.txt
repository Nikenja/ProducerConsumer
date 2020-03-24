project(test_helper)

set(SOURCE_FILES
    test_path.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
