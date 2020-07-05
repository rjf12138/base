project(base)
cmake_minimum_required(VERSION 3.10)
include_directories(./inc/)
link_directories(./lib/release/)

if(CMAKE_COMPILER_IS_GNUCXX)
    add_compile_options(-O2 -Wall -std=c++11)
    message(STATUS "optional:-std=c++11")
endif(CMAKE_COMPILER_IS_GNUCXX)

add_subdirectory(./src)
add_subdirectory(./main)
