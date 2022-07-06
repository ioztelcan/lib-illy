#include "sample_module.h"

#include "gtest/gtest.h"

TEST(sample_suite, hello_test)
{
    hello();
    SUCCEED();
}
