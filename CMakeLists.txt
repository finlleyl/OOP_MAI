cmake_minimum_required(VERSION 3.10)
project(lab2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(TESTS "Build tests" OFF)

add_executable(main src/main.cpp src/money.cpp)

target_include_directories(main PRIVATE include)

add_subdirectory(external/googletest)

add_executable(test tests/function_test.cpp src/money.cpp)

target_include_directories(test PRIVATE include)

target_link_libraries(test gtest gtest_main)