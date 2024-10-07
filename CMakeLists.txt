cmake_minimum_required(VERSION 3.10)
project(lab3)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(TESTS "Build tests" OFF)

add_executable(main src/main.cpp src/rectangle.cpp src/square.cpp src/trapezoid.cpp src/figure.cpp include/figurearray.h
        include/figure.h include/rectangle.h include/square.h include/trapezoid.h src/figurearray.cpp)

target_include_directories(main PRIVATE include)

add_subdirectory(external/googletest)

add_executable(test tests/test.cpp src/rectangle.cpp src/square.cpp src/trapezoid.cpp src/figure.cpp
        include/figure.h include/rectangle.h include/square.h include/trapezoid.h include/figurearray.h src/figurearray.cpp)

target_include_directories(test PRIVATE include)

target_link_libraries(test gtest gtest_main)