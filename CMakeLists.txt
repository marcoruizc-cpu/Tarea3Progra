cmake_minimum_required(VERSION 3.20)
project(untitled20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${CMAKE_SOURCE_DIR})

add_executable(untitled20 main.cpp
        core_numeric.h)

add_executable(test_sum tests/sum/test.cpp)
add_executable(test_mean tests/mean/test.cpp)
add_executable(test_variance tests/variance/test.cpp)
add_executable(test_max tests/max/test.cpp)
add_executable(test_transform_reduce tests/transform_reduce/test.cpp)
add_executable(test_variadic tests/variadic/test.cpp)
