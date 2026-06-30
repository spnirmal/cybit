cmake_minimum_required(VERSION 3.10)

project(launcher)

set(CMAKE_CXX_STANDARD 17)
find_package(Curses REQUIRED)

include_directories(inc ${CURSES_INCLUDE_DIR}) 

add_executable(launcher
	src/main.cpp
)

target_link_libraries(launcher ${CURSES_LIBRARIES})
