add_library(graph_coloring_lib STATIC
        CGraph.cpp
)

target_link_libraries(graph_coloring_lib sfml-graphics sfml-window sfml-system)
target_include_directories(graph_coloring_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})