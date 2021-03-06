cmake_minimum_required(VERSION 3.5)

project(cfd LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

include_directories(
    cfd
    ui
)

add_executable(cfd
    ui/main.cpp
    ui/mainwindow.cpp
    cfd/cfd.cpp
    ui/mainwindow.h
    ui/mainwindow.ui
)

target_link_libraries(cfd PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
