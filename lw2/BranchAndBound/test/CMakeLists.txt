include(GoogleTest)

add_executable(branch_and_bound_test
        GraphController_test.cpp
)

target_link_libraries(branch_and_bound_test PRIVATE GTest::GTest GTest::gtest_main branch_and_bound_lib)

gtest_discover_tests(branch_and_bound_test)
