project(Connect4_Lib)

add_executable(1p oneplayer.cpp)
target_link_libraries(1p PRIVATE connect4_lib)
