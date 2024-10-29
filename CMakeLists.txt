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
        Network
        SerialPort
)
qt_standard_project_setup()

set(PROJECT_SOURCES
    main.cpp
    mainwindow.h
    mainwindow.cpp
    interface/pages/BasePage.cpp
    interface/pages/home.cpp
    interface/pages/BatterySetting.cpp
    interface/widget/CycleProgressBar.cpp
    interface/pages/header/BasePage.h
    interface/pages/header/home.h
    interface/pages/header/BatterySetting.h
    interface/widget/Logger.h
    interface/widget/Logger.cpp
    func/logger/LogModel.cpp
    func/logger/LogModel.h
    func/comms/AbstractCommunication.cpp
    func/comms/AbstractCommunication.h
    func/comms/SerialCtl.cpp
    func/comms/SerialCtl.h
    func/comms/Communication.cpp
    func/comms/Communication.h
)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/interface/pages/header
    ${CMAKE_SOURCE_DIR}/interface/widget
    ${CMAKE_SOURCE_DIR}/func/logger
    ${CMAKE_SOURCE_DIR}/func/comms
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
        Qt::Network
        Qt::SerialPort
        ${CMAKE_SOURCE_DIR}/lib/elawidgettoolsd.lib
)

