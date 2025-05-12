set(target tests)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(${target} scan_table_test.cpp sort_table_test.cpp 
                array_hash_table_tests.cpp 
                list_hash_table_tests.cpp
              )
target_link_libraries(${target} GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(${target})