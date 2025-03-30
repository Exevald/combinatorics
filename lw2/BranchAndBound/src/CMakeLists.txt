add_executable(branch_and_bound
        CGraphController.cpp
        main.cpp
)

add_library(branch_and_bound_lib STATIC
        CGraphController.cpp
)

target_include_directories(branch_and_bound_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})