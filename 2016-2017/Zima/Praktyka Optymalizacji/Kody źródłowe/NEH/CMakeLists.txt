cmake_minimum_required(VERSION 3.5)
project(NEH)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Customer.cpp
    Customer.h
    main.cpp
    Solver.cpp
    Solver.h
    Task.cpp
    Task.h)

add_executable(NEH ${SOURCE_FILES})