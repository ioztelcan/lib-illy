#include <gtest/gtest.h>

#include <illy/util/overload.h>

#include <variant>

using namespace illy;
using ::testing::internal::CaptureStdout;
using ::testing::internal::GetCapturedStdout;

TEST(illy_overload, overloaded_lambda)
{
    overload_t identifier_func {
            [](int) {return "visiting with integer.";},
            [](std::string) {return "visiting with string.";},
            [](float) {return "visiting with float.";},
    };

    EXPECT_EQ(identifier_func(5), "visiting with integer.");
    EXPECT_EQ(identifier_func(5.3f), "visiting with float.");
    EXPECT_EQ(identifier_func("asd"), "visiting with string.");
}

TEST(illy_overload, visitor_pattern)
{
    overload_t identifier_func {
            [](int) {return "visiting with integer.";},
            [](std::string) {return "visiting with string.";},
            [](float) {return "visiting with float.";},
    };

    std::variant<int, std::string, float> var;
    var = 11;
    EXPECT_EQ(std::visit(identifier_func, var), "visiting with integer.");
    var = "asd";
    EXPECT_EQ(std::visit(identifier_func, var), "visiting with string.");
    var = 12.4f;
    EXPECT_EQ(std::visit(identifier_func, var), "visiting with float.");
}