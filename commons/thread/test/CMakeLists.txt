project(ithread_test)

find_package(Boost COMPONENTS system unit_test_framework REQUIRED)

set(TEST_NAME1 ithread_test)
set(TEST_NAME2 ithread_try_stop_routine_through_kill_test)

add_executable(${TEST_NAME1} ithread_test.cpp)
add_executable(${TEST_NAME2} ithread_try_stop_routine_through_kill_test.cpp)

target_compile_options(${TEST_NAME1} PRIVATE -Wall -Wextra -Wpedantic -Werror)
target_compile_options(${TEST_NAME2} PRIVATE -Wall -Wextra -Wpedantic -Werror)

add_test(${TEST_NAME1} ${TEST_NAME1})
add_test(${TEST_NAME2} ${TEST_NAME2})

target_link_libraries(${TEST_NAME1} ${Boost_LIBRARIES} thread)
target_link_libraries(${TEST_NAME2} ${Boost_LIBRARIES} thread)
