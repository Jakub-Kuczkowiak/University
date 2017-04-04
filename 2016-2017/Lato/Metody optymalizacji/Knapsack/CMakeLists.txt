cmake_minimum_required(VERSION 3.6)
project(Knapsack)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp Item.cpp Item.h Backpack.cpp Backpack.h Input.cpp Input.h Solver.cpp Solver.h)
add_executable(Knapsack ${SOURCE_FILES})