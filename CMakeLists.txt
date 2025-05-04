cmake_minimum_required(VERSION 3.27)
project(combinatorics)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

enable_testing()

add_subdirectory(lw2/BranchAndBound)
add_subdirectory(lw3/GraphColoring)