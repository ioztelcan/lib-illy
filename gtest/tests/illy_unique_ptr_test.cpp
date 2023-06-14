#include <illy/memory/unique_ptr.h>

#include <iostream>
#include <gtest/gtest.h>

using namespace illy;

class TestClass {
public:
    int a = 0;
};


TEST(illy_unique_ptr, default_ctor)
{
    unique_ptr<int> up1;
    EXPECT_EQ(up1, nullptr);
}

TEST(illy_unique_ptr, factory_function)
{
    auto up1 = make_unique<int>();
    EXPECT_NE(up1, nullptr);
}

TEST(illy_unique_ptr, dereference_operator)
{
    auto up1 = make_unique<int>(10);
    EXPECT_EQ(*up1, 10);
}

TEST(illy_unique_ptr, class_member_access_operator)
{
    auto up1 = make_unique<TestClass>(10);
    EXPECT_EQ(up1->a, 10);
}

TEST(illy_unique_ptr, ctor_with_pointer)
{
    unique_ptr<int> up1{new int};
    EXPECT_NE(up1, nullptr);

    auto *a = new TestClass{5};
    unique_ptr<TestClass> up2{a};
    EXPECT_EQ(up2->a, 5);
}

TEST(illy_unique_ptr, copy_ctor)
{
    unique_ptr<int> up1 = make_unique<int>(10);
    auto up2 = up1;

    EXPECT_EQ(*up1, 10);
    EXPECT_EQ(*up2, 10);
}

TEST(illy_unique_ptr, move_ctor)
{
    unique_ptr<int> up1 = make_unique<int>(10);
    auto up2 = std::move(up1);

    EXPECT_EQ(*up2, 10);
}

TEST(illy_unique_ptr, copy_assignment)
{
    unique_ptr<int> up1 = make_unique<int>(10);
    unique_ptr<int> up2;
    up2 = up1;

    EXPECT_EQ(*up1, 10);
    EXPECT_EQ(*up2, 10);
}

TEST(illy_unique_ptr, move_assignment)
{
    unique_ptr<int> up1 = make_unique<int>(10);
    unique_ptr<int> up2;
    up2 = std::move(up1);

    EXPECT_EQ(*up2, 10);
}

TEST(illy_unique_ptr, get_deleter)
{
    unique_ptr<int> up1 = make_unique<int>();
    auto i = new int;
    auto int_deleter = up1.get_deleter();

    EXPECT_NO_THROW(int_deleter(i));
}

TEST(illy_unique_ptr, release)
{
    unique_ptr<int> up1 = make_unique<int>(10);
    auto *p = up1.release();
    EXPECT_EQ(*p, 10);
    EXPECT_EQ(up1, nullptr);
    delete p;
}

TEST(illy_unique_ptr, reset)
{
    illy::unique_ptr<int> up1 = make_unique<int>(10);
    int *i = new int{5};
    up1.reset(i);
    EXPECT_EQ(*up1, 5);

    up1.reset();
    EXPECT_EQ(up1, nullptr);
}

TEST(illy_unique_ptr, member_swap)
{
    illy::unique_ptr<int> up1 = make_unique<int>(10);
    illy::unique_ptr<int> up2 = make_unique<int>(20);
    up1.swap(up2);

    EXPECT_EQ(*up1, 20);
    EXPECT_EQ(*up2, 10);
}

TEST(illy_unique_ptr, global_swap)
{
    illy::unique_ptr<int> up1 = make_unique<int>(10);
    illy::unique_ptr<int> up2 = make_unique<int>(20);
    std::swap(up1, up2);

    EXPECT_EQ(*up1, 20);
    EXPECT_EQ(*up2, 10);
}

TEST(illy_unique_ptr, get_copy)
{
    unique_ptr<int> up1 = make_unique<int>(10);
    auto up2 = up1.get_copy();

    EXPECT_EQ(*up1, *up2);
    EXPECT_NE(up1, up2);
}

TEST(illy_unique_ptr, equality_operator)
{
    unique_ptr<int> up1 = make_unique<int>(10);
    EXPECT_EQ(up1, up1);
}