cmake_minimum_required(VERSION 3.24)

project(tree_database VERSION 0.1 LANGUAGES CXX)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/macro.cmake)

AUTO_BUILD_RESOURCES_QT5()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED)

INCLUDE_SOURCES(tree_database})

set(QT_COMPONENTS
    QuickWidgets
    Core
    Qml
    QuickControls2
)

add_executable(${PROJECT_NAME}
    ${HEADERS}
    ${SOURCES}
    ${RESOURCES})

target_include_directories(tree_database
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

FIND_AND_LINK_QT(TARGET
    tree_database
    QT_COMPONENTS
    ${QT_COMPONENTS})

