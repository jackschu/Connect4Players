project(Connect4_Lib)

# All sources that also need to be tested in unit tests go into a static library

add_library(connect4_lib STATIC minimaxNode.cpp minimaxNode.h board.cpp board.h)
set_property(TARGET connect4_lib PROPERTY CXX_STANDARD 17)
target_include_directories(connect4_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# The main program
SET(CMAKE_EXECUTABLE_SUFFIX ".out")
add_executable(prog main.cpp)
target_link_libraries(prog PRIVATE connect4_lib)
