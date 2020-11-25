project(Connect4_Lib)

# All sources that also need to be tested in unit tests go into a static library
file(GLOB_RECURSE SOURCES  "./*.cpp")
file(GLOB_RECURSE HEADERS  "./*.h")

add_library(connect4_lib STATIC ${SOURCES} ${HEADERS})
set_target_properties(connect4_lib PROPERTIES LINKER_LANGUAGE CXX)

set_property(TARGET connect4_lib PROPERTY CXX_STANDARD 17)
target_include_directories(connect4_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options(connect4_lib PRIVATE -Werror -Wall -Wextra -O3)

# The main program
SET(CMAKE_EXECUTABLE_SUFFIX ".out")
add_executable(prog main.cpp)
target_link_libraries(prog PRIVATE connect4_lib)

