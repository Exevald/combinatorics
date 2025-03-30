cmake_minimum_required(VERSION 3.27)
project(combinatorics)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)

enable_testing()

add_subdirectory(lw2/BranchAndBound)
