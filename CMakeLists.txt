cmake_minimum_required(VERSION 3.16)
project(SwapBatterySystem LANGUAGES CXX)

include(qt.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR}
    COMPONENTS
        Core
        Gui
        Widgets
)
qt_standard_project_setup()

set(PROJECT_SOURCES
    main.cpp
    mainwindow.ui
    mainwindow.h
    mainwindow.cpp
)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

qt_add_executable(SwapBatterySystem ${PROJECT_SOURCES} include/ElaWidgetTools.qrc)

set_target_properties(SwapBatterySystem
    PROPERTIES
        WIN32_EXECUTABLE TRUE
)

target_link_libraries(SwapBatterySystem
    PUBLIC
        Qt::Core
        Qt::Gui
        Qt::Widgets
        ${CMAKE_SOURCE_DIR}/lib/elawidgettoolsd.lib
)

