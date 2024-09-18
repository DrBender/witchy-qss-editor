cmake_minimum_required(VERSION 3.16)

project(test_qss LANGUAGES CXX)

enable_testing()

find_package(QT NAMES Qt5 COMPONENTS Test REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Test REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(test_parse test_parse.cpp ../editor/Parser.h ../editor/Parser.cpp)
add_test(NAME ParseTest COMMAND test_parse)

target_link_libraries(test_parse PRIVATE Qt${QT_VERSION_MAJOR}::Test)

