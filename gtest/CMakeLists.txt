project(utillyty-test LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.13.0
)

set(gtest_force_shared_crt
    ON
    CACHE BOOL "" FORCE)
set(gmock_BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)
set(gtest_BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)
  
FetchContent_MakeAvailable(googletest)
  
# Add test source files
set(TEST_SRC_DIR tests CACHE PATH "Test source files directory.")

set(TEST_SOURCES
  ${TEST_SRC_DIR}/utillyty_print_test.cpp
  ${TEST_SRC_DIR}/utillyty_overload_test.cpp
  ${TEST_SRC_DIR}/utillyty_unique_ptr_test.cpp
        )

set(BUILD_GMOCK ON)

# Create the test executable
add_executable(${PROJECT_NAME} ${TEST_SOURCES} ${TEST_SRC_DIR}/gtest_main.cpp)

# Link against Google Test and mylibrary
target_link_libraries(${PROJECT_NAME} PRIVATE utillyty gtest gmock)

# Start GTest
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

