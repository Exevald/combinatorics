include(GoogleTest)

add_executable(max_flow_problem_test
        MaxFlowProblem_test.cpp
)
target_link_libraries(max_flow_problem_test PRIVATE GTest::GTest GTest::gtest_main sfml-graphics sfml-window sfml-system max_flow_problem_lib)

gtest_discover_tests(max_flow_problem_test)