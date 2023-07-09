cmake_minimum_required(VERSION 3.24)

project(micrantask VERSION 0.1 LANGUAGES CXX)

include(${CMAKE_CURRENT_LIST_DIR}/cmake/macro.cmake)

AUTO_BUILD_RESOURCES_QT5()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED)

INCLUDE_SOURCES(${PROJECT_NAME})

set(QT_COMPONENTS
    Core Widgets
    QuickWidgets
    Core
    Qml
    QuickControls2
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${RESOURCES})

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

FIND_AND_LINK_QT(TARGET
    ${PROJECT_NAME}
    QT_COMPONENTS
    ${QT_COMPONENTS})

