cmake_minimum_required(VERSION 3.10)
project(launcher)

set(CMAKE_CXX_STANDARD 17)
find_package(Curses REQUIRED)

add_executable(launcher
        src/main.cpp
        src/application_window.cpp
        src/launcher_screen.cpp
        src/terminal_window.cpp
        src/focus.cpp
        src/window.cpp
)

# Modern approach: Scope includes specifically to the 'launcher' target
target_include_directories(launcher PRIVATE inc)
target_link_libraries(launcher ${CURSES_LIBRARIES})   
