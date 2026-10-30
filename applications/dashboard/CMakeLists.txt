cmake_minimum_required(VERSION 3.22)

project(cybitdashboard LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(cybit
    src/main.cpp
)

qt_add_qml_module(cybit
    URI Cybit
    VERSION 1.0
    QML_FILES
        ui/Main.qml
    RESOURCES
        assets/image.png
)

target_link_libraries(cybit
    PRIVATE Qt6::Quick
)
