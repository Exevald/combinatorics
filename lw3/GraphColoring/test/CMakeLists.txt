include(GoogleTest)

add_executable(graph_coloring_test
        GraphColoring_test.cpp
)
target_link_libraries(graph_coloring_test PRIVATE GTest::GTest GTest::gtest_main sfml-graphics sfml-window sfml-system graph_coloring_lib)

gtest_discover_tests(graph_coloring_test)
