cmake_minimum_required(VERSION 3.10)
project(lab4)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(main src/main.cpp
        include/figurearray.h include/figure.h include/rectangle.h include/square.h include/trapezoid.h include/point.h include/concepts.h)

target_include_directories(main PRIVATE include)

add_subdirectory(external/googletest)

add_executable(test tests/test.cpp
        include/figurearray.h include/figure.h include/rectangle.h include/square.h include/trapezoid.h include/point.h include/concepts.h)

target_include_directories(test PRIVATE include)

target_link_libraries(test gtest gtest_main)
