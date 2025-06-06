add_library(matching_lib STATIC
        MaxMatchingSolver.cpp
        Matrix.cpp
        Matrix.h
)

target_link_libraries(matching_lib)
target_include_directories(matching_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})