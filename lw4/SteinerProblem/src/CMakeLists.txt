add_library(steiner_problem_lib STATIC
        Graph.cpp
)

target_link_libraries(steiner_problem_lib sfml-graphics sfml-window sfml-system)
target_include_directories(steiner_problem_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})