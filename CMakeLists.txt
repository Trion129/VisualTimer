cmake_minimum_required(VERSION 3.5)
project(VISUALTIMER VERSION 1.0)

# Set installation directories
include(GNUInstallDirs)

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

# Installation rules
install(TARGETS VisualTimer
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Install desktop file
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/visualtimer.desktop.in
    ${CMAKE_CURRENT_BINARY_DIR}/resources/visualtimer.desktop
    @ONLY
)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/resources/visualtimer.desktop
    DESTINATION ${CMAKE_INSTALL_DATADIR}/applications
)

# Install icon
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/resources/icons/timer_icon.svg
    DESTINATION ${CMAKE_INSTALL_DATADIR}/icons/hicolor/scalable/apps
    RENAME visualtimer.svg
)