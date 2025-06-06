include(GoogleTest)

set(FILES
        ${CMAKE_SOURCE_DIR}/lw6/Matching/test/data/cycleGraph.txt
        ${CMAKE_SOURCE_DIR}/lw6/Matching/test/data/emptyGraph.txt
        ${CMAKE_SOURCE_DIR}/lw6/Matching/test/data/fullGraph.txt
        ${CMAKE_SOURCE_DIR}/lw6/Matching/test/data/largeGraph.txt
        ${CMAKE_SOURCE_DIR}/lw6/Matching/test/data/lineGraph.txt
        ${CMAKE_SOURCE_DIR}/lw6/Matching/test/data/ordinaryGraph.txt
        ${CMAKE_SOURCE_DIR}/lw6/Matching/test/data/bipartiteGraph.txt
)

add_executable(matching_test
        MaxMatching_test.cpp
)
target_link_libraries(matching_test PRIVATE GTest::GTest GTest::gtest_main matching_lib)
gtest_discover_tests(matching_test)

foreach (file ${FILES})
    add_custom_command(
            TARGET matching_test POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy ${file} ${CMAKE_BINARY_DIR}/lw6/Matching/test
    )
endforeach ()