project(Connect4_tests)

# The test program

SET(CMAKE_EXECUTABLE_SUFFIX ".out")
add_executable(tests testmain.cpp)
target_link_libraries(tests PRIVATE connect4_lib catch)
add_test(libtests tests.out)
