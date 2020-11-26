cmake_minimum_required(VERSION 3.0)

enable_testing()
project(Connect4 VERSION 0.1
				 DESCRIPTION "Connect 4 simulator"
				 LANGUAGES CXX)
#add_subdirectory(thirdparty/catch2)
#add_subdirectory(src)
#add_subdirectory(apps)
#add_subdirectory(test)
file(GLOB_RECURSE SOURCES "src/*.cpp")


add_executable(a
	${SOURCES}
)
set_target_properties(a PROPERTIES LINK_FLAGS "--bind -s WASM=0 -s EXPORT_ES6=1 -s USE_ES6_IMPORT_META=0 -s MODULARIZE=1")
#set_target_properties(a PROPERTIES LINK_FLAGS "-O3 --bind -s WASM=0 --closure 1")


