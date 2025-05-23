cmake_minimum_required(VERSION 3.5)
project(VISUALTIMER VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

include_directories(include)

set(SOURCES
    ui/mainwindow.ui
    src/main.cpp
    src/mainwindow.cpp
    src/timer.cpp
    src/timerdial.cpp
)

set(RESOURCES
    resources/icons.qrc
)

qt5_add_resources(RESOURCE_SOURCES ${RESOURCES})

add_executable(VisualTimer ${SOURCES} ${RESOURCE_SOURCES})

target_link_libraries(VisualTimer Qt5::Widgets)