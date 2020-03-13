cmake_minimum_required(VERSION 3.2)

project(main_test_project)

find_package(Boost COMPONENTS system unit_test_framework REQUIRED)

add_executable(main_test main_test.cpp)

set_target_properties(main_test PROPERTIES
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

target_link_libraries(main_test ${Boost_LIBRARIES} autots)
