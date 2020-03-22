project(Connect4_tests)

# The test program

add_executable(tests testmain.cpp)
target_link_libraries(tests PRIVATE connect4_lib catch)
add_test(testname tests)
