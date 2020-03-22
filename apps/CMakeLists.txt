project(Connect4_Lib)

SET(CMAKE_EXECUTABLE_SUFFIX ".out")
add_executable(1p oneplayer.cpp)
target_link_libraries(1p PRIVATE connect4_lib)
