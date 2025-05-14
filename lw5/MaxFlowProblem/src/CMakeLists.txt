add_library(max_flow_problem_lib STATIC
        Graph.cpp
)

target_link_libraries(max_flow_problem_lib sfml-graphics sfml-window sfml-system)
target_include_directories(max_flow_problem_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})