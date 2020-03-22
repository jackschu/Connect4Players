cmake_minimum_required(VERSION 3.0)


enable_testing()
project(Connect4 VERSION 0.1
				 DESCRIPTION "Connect 4 simulator"
				 LANGUAGES CXX)

add_subdirectory(thirdparty/catch2)
add_subdirectory(src)
add_subdirectory(apps)
add_subdirectory(test)
