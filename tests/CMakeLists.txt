cmake_minimum_required(VERSION 3.14)
project(test_qss_editor)

find_package(Qt5 REQUIRED Test)

add_executable(test_qss_editor myclasstest.cpp)
target_link_libraries(test_qss_editor Qt5::Test myclass)

add_test(NAME ParseTest COMMAND test_qss_editor)
