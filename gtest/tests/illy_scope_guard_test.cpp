#include <gtest/gtest.h>

#include <illy/util/scope_guard.h>
#include <memory>

bool b = false;
void func()
{
    b = true;
}

TEST(illy_scope_guard, default_constructor)
{
    illy::scope_guard<std::function<void()>> sc{};
}

TEST(illy_scope_guard, lambda_1)
{
    bool a = false;
    {
        illy::scope_guard sc{[&a]() { a = true; }};
    }
    EXPECT_TRUE(a);
}

TEST(illy_scope_guard, lambda_2)
{
    bool a = false;
    auto fn = [&a]() { a = true; };
    {
        illy::scope_guard sc{fn};
    }
    EXPECT_TRUE(a);
}

TEST(illy_scope_guard, move_constructor)
{
    bool a = false;
    {
        illy::scope_guard sc{[&a]() { a = true; }};
        illy::scope_guard sc2{std::move(sc)};
    }
    EXPECT_TRUE(a);
}

TEST(illy_scope_guard, release)
{
    bool a = false;
    {
        illy::scope_guard sc{[&a]() { a = true; }};
        sc.release();
    }
    EXPECT_FALSE(a);
}

TEST(illy_scope_guard, free_function)
{
    {
        illy::scope_guard sc{func};
    }
    EXPECT_TRUE(b);
}

TEST(illy_scope_guard, dynamic_memory)
{
    std::shared_ptr<int[]> s1 (new int[100]);
    {
        illy::scope_guard sc {[sp = s1](){ EXPECT_EQ(sp.use_count(), 2); }};
    }
    EXPECT_EQ(s1.use_count(), 1);
}