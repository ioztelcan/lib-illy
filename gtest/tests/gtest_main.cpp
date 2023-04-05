#include <gtest/gtest.h>

// The main function must be defined in the test file
int main(int argc, char** argv) {
  // Initialize Google Test
  ::testing::InitGoogleTest(&argc, argv);
  //::testing::InitGoogleMock(&argc, argv);

  // Run all tests
  return RUN_ALL_TESTS();
}

