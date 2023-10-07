cmake_minimum_required(VERSION 3.10)
project(gtest)

add_executable(main main.cpp funcky.cpp)

enable_testing()

find_package(GTest REQUIRED)

add_subdirectory(googletest) 
include_directories(googletest/googletest/include)

add_executable(test1 test1.cpp  funcky.cpp)
target_link_libraries(test1 ${GTEST_LIBRARIES})

add_test(NAME BASIC COMMAND test1)