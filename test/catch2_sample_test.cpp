#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "sample_module.h"

TEST_CASE("Sample Module Hello", "[hello]")
{
    hello();
}