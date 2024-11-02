cmake_minimum_required(VERSION 3.10)
project(lab5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(TESTS "Build tests" OFF)

add_executable(main
        src/custom_mr.cpp
        include/custom_mr.hpp
        include/dynamic_array.hpp
        src/main.cpp)

target_include_directories(main PRIVATE include)

add_subdirectory(external/googletest)

add_executable(test
        src/custom_mr.cpp
        include/custom_mr.hpp
        include/dynamic_array.hpp
        tests/test.cpp)

target_include_directories(test PRIVATE include)

target_link_libraries(test gtest gtest_main)