cmake_minimum_required(VERSION 3.1...3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

project(LogAnalyzer
    DESCRIPTION
        "HR Challenge for UI/UX"
    LANGUAGES
        CXX
)

find_package(Qt5 COMPONENTS Core Qml Gui REQUIRED)

add_executable(LogAnalyzer "")

target_sources(LogAnalyzer
    PRIVATE
        qml.qrc
        main.cpp
        LogController.h
        LogController.cpp
        LogModel.h
        LogModel.cpp
        LogData.h
)

target_link_libraries(LogAnalyzer
    Qt::Gui
    Qt::Core
    Qt::Qml
)

install(
    TARGETS
        LogAnalyzer
    DESTINATION
        ${CMAKE_INSTALL_PREFIX}/bin
)

