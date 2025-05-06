include(GoogleTest)

add_executable(steiner_problem_test
        SteinerProblem_test.cpp
)
target_link_libraries(steiner_problem_test PRIVATE GTest::GTest GTest::gtest_main sfml-graphics sfml-window sfml-system steiner_problem_lib)

gtest_discover_tests(steiner_problem_test)
