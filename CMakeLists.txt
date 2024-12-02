cmake_minimum_required(VERSION 3.16)
project(SwapBatterySystem LANGUAGES CXX)

include(qt.cmake)

set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR}
    COMPONENTS
        Core
        Gui
        Widgets
        Network
        SerialPort
)
qt_standard_project_setup()

# 动态获取文件夹下的.h .cpp 文件
file(GLOB PAGES_FILES 
    src/interface/pages/header/*.h
    src/interface/pages/base/*.cpp
    src/interface/pages/base/*.h
    src/interface/pages/*.cpp
    src/interface/pages/custom/*.cpp
    src/interface/pages/custom/*.h
    src/interface/Model/*.h
    src/interface/Model/*.cpp
)
file(GLOB WIDGET_FILES
    src/interface/widget/*.h
    src/interface/widget/*.cpp
)
file(GLOB FUNC_FILES
    src/func/logger/*.h
    src/func/logger/*.cpp
    src/func/comms/*.h
    src/func/comms/*.cpp
    src/func/comms/class/*.h
    src/func/comms/class/*.cpp
    src/func/comms/driver/*.h
    src/func/comms/driver/*.cpp
    src/func/comms/driver/abstract/*.h
    src/func/comms/driver/abstract/*.cpp
    src/func/comms/thread/*.cpp
    src/func/comms/thread/*.h
    src/func/modbus/*.cpp
    src/func/modbus/*.h
    src/func/modbus/util/*.h
    src/func/modbus/util/*.cpp
)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.h
    mainwindow.cpp
    mainwindow.qrc

    ${FUNC_FILES}
    ${PAGES_FILES}
    ${WIDGET_FILES}
)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src/interface/pages/header
    ${CMAKE_SOURCE_DIR}/src/interface/pages/custom
    ${CMAKE_SOURCE_DIR}/src/interface/pages/base
    ${CMAKE_SOURCE_DIR}/src/interface/widget
    ${CMAKE_SOURCE_DIR}/src/interface/Model
    ${CMAKE_SOURCE_DIR}/src/func/logger
    ${CMAKE_SOURCE_DIR}/src/func/comms
    ${CMAKE_SOURCE_DIR}/src/func/comms/class
    ${CMAKE_SOURCE_DIR}/src/func/comms/driver
    ${CMAKE_SOURCE_DIR}/src/func/comms/driver/abstract
    ${CMAKE_SOURCE_DIR}/src/func/comms/thread
    ${CMAKE_SOURCE_DIR}/src/func/modbus/util
    ${CMAKE_SOURCE_DIR}/src/func/modbus
    ${CMAKE_SOURCE_DIR}/src/util
    ${CMAKE_SOURCE_DIR}
)

qt_add_executable(SwapBatterySystem ${PROJECT_SOURCES} include/ElaWidgetTools.qrc main.rc)

set_target_properties(SwapBatterySystem
    PROPERTIES
        WIN32_EXECUTABLE TRUE
)

target_link_libraries(SwapBatterySystem
    PUBLIC
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Network
        Qt::SerialPort
        ${CMAKE_SOURCE_DIR}/lib/elawidgettools.lib
)

get_property(TARGETS DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY BUILDSYSTEM_TARGETS)
message(STATUS "Available targets: ${TARGETS}")