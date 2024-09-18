cmake_minimum_required(VERSION 3.14)
project(
  qss_editor
  VERSION 0.0.1
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(
  Qt5
  COMPONENTS Core Widgets
  REQUIRED)

message(STATUS "Qt version: ${Qt5Core_VERSION}")

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build_cmake)
# Compile command export for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(COMPILE_COMMANDS_OUTPUT_DIR ${CMAKE_SOURCE_DIR})
set(SOURCES
    main.cpp
    MainWindow.cpp
    editor/QssTextEditor.cpp
    editor/SyntaxHighlighter.cpp
    editor/Parser.cpp
    editor/LineNumberArea.cpp
    preview/QssWidgetsPreview.cpp
    config/settings.cpp)
set(HEADERS
    MainWindow.h
    editor/QssTextEditor.h
    editor/SyntaxHighlighter.h
    editor/Parser.h
    editor/LineNumberArea.h
    preview/QssWidgetsPreview.h
    config/settings.h)
set(RESOURCES res/res.qrc)

set(ALL_SOURCES ${SOURCES} ${HEADERS} ${RESOURCES})

add_executable(qss_editor ${ALL_SOURCES})

target_include_directories(qss_editor PRIVATE editor preview config res)

target_link_libraries(qss_editor Qt5::Widgets)

add_subdirectory(tests)

add_custom_target(
  copy_compile_commands ALL
  COMMAND
    ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_BINARY_DIR}/compile_commands.json
    ${COMPILE_COMMANDS_OUTPUT_DIR}/compile_commands.json
  DEPENDS ${CMAKE_BINARY_DIR}/compile_commands.json
  COMMENT "Coping compile_commands.json")

