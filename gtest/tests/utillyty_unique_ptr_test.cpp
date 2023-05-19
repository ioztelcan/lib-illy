#include <utillyty/unique_ptr.h>

#include <iostream>
#include <gtest/gtest.h>

using namespace illy;

class TestClass2 {
public:
    TestClass2()
    {
        std::cout << "Constructed " << this << "\n";
    }

    explicit TestClass2(int in) : a{in}
    {
        std::cout << "Constructed " << this << " with " << in << "\n";
    }

    TestClass2(const TestClass2& other)
    {
        std::cout << "Copy constructed " << this << "\n";
        a = other.a;
    }

    TestClass2(TestClass2&& other) noexcept
    {
        std::cout << "Move constructed " << this << "\n";
        a = other.a;
    }

    ~TestClass2()
    {
        std::cout << "Destroyed " << this << "\n";
    }

    int a = 0;
};


class TestClass {
public:
    TestClass()
    {
        std::cout << "Constructed " << this << "\n";
    }

    explicit TestClass(int in) : a{in}
    {
        std::cout << "Constructed " << this << " with " << in << "\n";
    }

    TestClass(const TestClass& other)
    {
        std::cout << "Copy constructed " << this << "\n";
        a = other.a;
    }

    TestClass(TestClass&& other) noexcept
    {
        std::cout << "Move constructed " << this << "\n";
        a = other.a;
    }

    ~TestClass()
    {
        std::cout << "Destroyed " << this << "\n";
    }

    int a = 0;
};


TEST(utillyty_unique_ptr, default_ctor)
{
    unique_ptr<int> up1;
    EXPECT_EQ(up1, nullptr);
}

TEST(utillyty_unique_ptr, factory_function)
{
    auto up1 = make_unique<int>();
    EXPECT_NE(up1, nullptr);
}

TEST(utillyty_unique_ptr, dereference_operator)
{
    auto up1 = make_unique<int>(10);
    EXPECT_EQ(*up1, 10);
}

TEST(utillyty_unique_ptr, class_member_access_operator)
{
    auto up1 = make_unique<TestClass>(10);
    EXPECT_EQ(up1->a, 10);
}

TEST(utillyty_unique_ptr, ctor_with_pointer)
{
    unique_ptr<int> up1{new int};
    EXPECT_NE(up1, nullptr);

    auto *a = new TestClass{5};
    unique_ptr<TestClass> up2{a};
    EXPECT_EQ(up2->a, 5);
}

TEST(utillyty_unique_ptr, copy_ctor)
{
    unique_ptr<int> up1 = make_unique<int>(10);
    auto up2 = up1;

    EXPECT_EQ(*up1, 10);
    EXPECT_EQ(*up2, 10);
}

TEST(utillyty_unique_ptr, move_ctor)
{
    unique_ptr<int> up1 = make_unique<int>(10);
    auto up2 = std::move(up1);

    EXPECT_EQ(*up2, 10);
}

TEST(utillyty_unique_ptr, copy_assignment)
{
    unique_ptr<int> up1 = make_unique<int>(10);
    unique_ptr<int> up2;
    up2 = up1;

    EXPECT_EQ(*up1, 10);
    EXPECT_EQ(*up2, 10);
}

TEST(utillyty_unique_ptr, move_assignment)
{
    unique_ptr<int> up1 = make_unique<int>(10);
    unique_ptr<int> up2;
    up2 = std::move(up1);

    EXPECT_EQ(*up2, 10);
}

TEST(utillyty_unique_ptr, get_deleter)
{
    unique_ptr<int> up1 = make_unique<int>();
    auto i = new int;
    auto int_deleter = up1.get_deleter();

    EXPECT_NO_THROW(int_deleter(i));
}

TEST(utillyty_unique_ptr, release)
{
    unique_ptr<int> up1 = make_unique<int>(10);
    auto *p = up1.release();
    EXPECT_EQ(*p, 10);
    EXPECT_EQ(up1, nullptr);
    delete p;
}

TEST(utillyty_unique_ptr, reset)
{
    illy::unique_ptr<int> up1 = make_unique<int>(10);
    int *i = new int{5};
    up1.reset(i);
    EXPECT_EQ(*up1, 5);

    up1.reset();
    EXPECT_EQ(up1, nullptr);
}

TEST(utillyty_unique_ptr, member_swap)
{
    illy::unique_ptr<int> up1 = make_unique<int>(10);
    illy::unique_ptr<int> up2 = make_unique<int>(20);
    up1.swap(up2);

    EXPECT_EQ(*up1, 20);
    EXPECT_EQ(*up2, 10);
}

TEST(utillyty_unique_ptr, global_swap)
{
    illy::unique_ptr<int> up1 = make_unique<int>(10);
    illy::unique_ptr<int> up2 = make_unique<int>(20);
    std::swap(up1, up2);

    EXPECT_EQ(*up1, 20);
    EXPECT_EQ(*up2, 10);
}

TEST(utillyty_unique_ptr, playground)
{
    std::cout << "Test started\n";

    illy::unique_ptr<TestClass2> up1;

    if (up1) {
        std::cout << "Shouldn't display this.\n";
    }

    illy::unique_ptr<TestClass2> up2(new TestClass2);

    if (up2) {
        std::cout << "Should display this.\n";
    }

    up2->a = 5;

    std::cout << (*up2).a << "\n";

}

TEST(utillyty_unique_ptr, playground2)
{
    illy::unique_ptr<TestClass2> up1(new TestClass2);

    up1->a = 10;

    auto up2 = up1.get_copy();

    std::cout << up1->a << "\n";
    std::cout << up2->a << "\n";
}

TEST(utillyty_unique_ptr, playground3)
{
    illy::unique_ptr<TestClass2> up1(new TestClass2);

    up1->a = 10;

    illy::unique_ptr<TestClass2> up2;
    up2 = std::move(up1);

    if (!up1) {
        std::cout << "first is null\n";
    }

    std::cout << "up2: " << up2->a << "\n";

}

TEST(utillyty_unique_ptr, playground4)
{
    illy::unique_ptr<TestClass2> up1(new TestClass2);
    up1->a = 10;

    illy::unique_ptr<TestClass2> up2;
    illy::unique_ptr<TestClass2> up3;

    up2.operator=(up1);
    up3 = up1;

    std::cout << up1->a << " " << up2->a << " " << up3->a << "\n";

}

TEST(utillyty_unique_ptr, playground5)
{
    auto up = illy::make_unique<TestClass2>();
    up->a = 5;
    std::cout << up->a << "\n";
}

TEST(utillyty_unique_ptr, playground6)
{
    auto up = illy::make_unique<TestClass2>();
    up->a = 5;
    std::cout << up->a << "\n";
    illy::unique_ptr<TestClass2> up2{std::move(up)};
    std::cout << up2->a << "\n";
}

TEST(utillyty_unique_ptr, playground7)
{
    auto up = illy::make_unique<TestClass2>();
    up->a = 5;
    std::cout << up->a << "\n";
    illy::unique_ptr<TestClass2> up2{up};
    std::cout << up->a << "\n";
    std::cout << up2->a << "\n";
}

TEST(utillyty_unique_ptr, playground8)
{
    illy::unique_ptr<int> ip1{new int};
    illy::unique_ptr<int> ip2{new int};

    *ip1 = 10;
    *ip2 = 5;

    std::cout << (ip1 == ip2) << "\n";

    if (ip1 < ip2) {
        std::cout << "less\n";
    } else {
        std::cout << "more\n";
    }
}