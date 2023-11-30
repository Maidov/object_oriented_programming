cmake_minimum_required(VERSION 3.10)
project(lab_4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O")

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${SOURCE_DIR})
include_directories(${INCLUDE_DIR})

add_executable(${CMAKE_PROJECT_NAME}.exe main.cpp)


enable_testing()

add_executable(tests_lab.exe ${TEST_DIR}/test.cpp)
target_link_libraries(tests_lab.exe ${GTEST_LIBRARIES})

add_test(NAME BASIC COMMAND tests_lab.exe)