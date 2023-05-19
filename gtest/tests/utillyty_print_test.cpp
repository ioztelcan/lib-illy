#include <gtest/gtest.h>

#include <utillyty/print.h>

using namespace illy;
using ::testing::internal::CaptureStdout;
using ::testing::internal::GetCapturedStdout;

class TestClass {
public:
    friend std::ostream& operator<<(std::ostream &os, const TestClass &tc);
private:
    int a_ {1};
    std::string s_ {"test-class"};
};

std::ostream& operator<<(std::ostream &os, const TestClass &tc)
{
    os << tc.a_ << " | " << tc.s_ << "\n";
    return os;
}

TEST(utillyty_print, primitives)
{
    CaptureStdout();
    print(10);
    EXPECT_EQ(GetCapturedStdout(), "10\n");

    CaptureStdout();
    print(4.5);
    EXPECT_EQ(GetCapturedStdout(), "4.5\n");

    CaptureStdout();
    print(6.32f);
    EXPECT_EQ(GetCapturedStdout(), "6.32\n");

    CaptureStdout();
    int a = 5;
    print(a);
    EXPECT_EQ(GetCapturedStdout(), "5\n");

    CaptureStdout();
    double b = 3.14;
    print(b);
    EXPECT_EQ(GetCapturedStdout(), "3.14\n");

    CaptureStdout();
    float c = 1.001;
    print(c);
    EXPECT_EQ(GetCapturedStdout(), "1.001\n");

    CaptureStdout();
    int d = -10;
    print(d);
    EXPECT_EQ(GetCapturedStdout(), "-10\n");

    CaptureStdout();
    long long e = 200;
    print(e);
    EXPECT_EQ(GetCapturedStdout(), "200\n");
}

TEST(utillyty_print, char_and_string)
{
    CaptureStdout();
    char a = 'A';
    print(a);
    EXPECT_EQ(GetCapturedStdout(), "A\n");

    CaptureStdout();
    const char b[] = "asd";
    print(b);
    EXPECT_EQ(GetCapturedStdout(), "asd\n");

    CaptureStdout();
    std::string c = "asd";
    print(c);
    EXPECT_EQ(GetCapturedStdout(), "asd\n");

    CaptureStdout();
    print("message");
    EXPECT_EQ(GetCapturedStdout(), "message\n");
}

TEST(utillyty_print, stl_container_adapters)
{
    std::stack<int> mstack{};
    CaptureStdout();
    print(mstack);
    EXPECT_EQ(GetCapturedStdout(), "[ ]\n");
    mstack.push(100);
    mstack.push(101);
    mstack.push(102);
    CaptureStdout();
    print(mstack);
    EXPECT_EQ(GetCapturedStdout(), "[ 102 101 100 ]\n");

    std::queue<int> mqueue{};
    CaptureStdout();
    print(mqueue);
    EXPECT_EQ(GetCapturedStdout(), "[ ]\n");
    mqueue.push(200);
    mqueue.push(201);
    mqueue.push(202);
    CaptureStdout();
    print(mqueue);
    EXPECT_EQ(GetCapturedStdout(), "[ 200 201 202 ]\n");

    std::priority_queue<int> mpqueue{};
    CaptureStdout();
    print(mpqueue);
    EXPECT_EQ(GetCapturedStdout(), "[ ]\n");
    mpqueue.push(300);
    mpqueue.push(301);
    mpqueue.push(302);
    CaptureStdout();
    print(mpqueue);
    EXPECT_EQ(GetCapturedStdout(), "[ 302 301 300 ]\n");
}

TEST(utillyty_print, stl_containers)
{
    std::vector<int> ivec {1,2,3,4,5};
    CaptureStdout();
    print(ivec);
    EXPECT_EQ(GetCapturedStdout(), "[ 1 2 3 4 5 ]\n");

    std::vector<std::string> svec {"asd","zxc","qwe"};
    CaptureStdout();
    print(svec);
    EXPECT_EQ(GetCapturedStdout(), "[ asd zxc qwe ]\n");

    std::list<int> ilist {2,4,6,8};
    CaptureStdout();
    print(ilist);
    EXPECT_EQ(GetCapturedStdout(), "[ 2 4 6 8 ]\n");

    std::forward_list<int> iflist {5,6,7,8};
    CaptureStdout();
    print(iflist);
    EXPECT_EQ(GetCapturedStdout(), "[ 5 6 7 8 ]\n");

    std::deque<int> idq {10,11,12,13};
    CaptureStdout();
    print(idq);
    EXPECT_EQ(GetCapturedStdout(), "[ 10 11 12 13 ]\n");

    std::set<int> iset {20,30,40,50,60};
    CaptureStdout();
    print(iset);
    EXPECT_EQ(GetCapturedStdout(), "[ 20 30 40 50 60 ]\n");

    std::multiset<int> imset {20,30,40,40,40,50,60};
    CaptureStdout();
    print(imset);
    EXPECT_EQ(GetCapturedStdout(), "[ 20 30 40 40 40 50 60 ]\n");

    std::unordered_set<int> myuoset = {23,45,23,45};
    CaptureStdout();
    print(myuoset);
    EXPECT_EQ(GetCapturedStdout(), "[ 45 23 ]\n");

    std::unordered_multiset<int> myuoset2 = {23,45,23,45};
    CaptureStdout();
    print(myuoset2);
    EXPECT_EQ(GetCapturedStdout(), "[ 45 45 23 23 ]\n");

    std::array arr {5,4,3,2,1};
    CaptureStdout();
    print(arr);
    EXPECT_EQ(GetCapturedStdout(), "[ 5 4 3 2 1 ]\n");
}

TEST(utillyty_print, iterators)
{
    std::vector<int> ivec {1,2,3,4,5};
    CaptureStdout();
    print(ivec.begin(), ivec.end());
    EXPECT_EQ(GetCapturedStdout(), "[ 1 2 3 4 5 ]\n");

    std::vector<std::string> svec {"asd","zxc","qwe"};
    CaptureStdout();
    print(svec.begin(), svec.end());
    EXPECT_EQ(GetCapturedStdout(), "[ asd zxc qwe ]\n");

    std::list<int> ilist {2,4,6,8};
    CaptureStdout();
    print(ilist.begin(), ilist.end());
    EXPECT_EQ(GetCapturedStdout(), "[ 2 4 6 8 ]\n");

    std::forward_list<int> iflist {5,6,7,8};
    CaptureStdout();
    print(iflist.begin(), iflist.end());
    EXPECT_EQ(GetCapturedStdout(), "[ 5 6 7 8 ]\n");

    std::deque<int> idq {10,11,12,13};
    CaptureStdout();
    print(idq.begin(), idq.end());
    EXPECT_EQ(GetCapturedStdout(), "[ 10 11 12 13 ]\n");

    std::set<int> iset {20,30,40,50,60};
    CaptureStdout();
    print(iset.begin(), iset.end());
    EXPECT_EQ(GetCapturedStdout(), "[ 20 30 40 50 60 ]\n");

    std::multiset<int> imset {20,30,40,40,40,50,60};
    CaptureStdout();
    print(imset.begin(), imset.end());
    EXPECT_EQ(GetCapturedStdout(), "[ 20 30 40 40 40 50 60 ]\n");

    std::array arr {5,4,3,2,1};
    CaptureStdout();
    print(arr.begin(), arr.end());
    EXPECT_EQ(GetCapturedStdout(), "[ 5 4 3 2 1 ]\n");
}

TEST(utillyty_print, c_array)
{
    int ca[5] = {1,2,3};
    CaptureStdout();
    print(ca);
    EXPECT_EQ(GetCapturedStdout(), "[ 1 2 3 0 0 ]\n");
}

TEST(utillyty_print, stl_maps)
{
    std::map<char,int> cmap{{'a',1},{'b',2}};
    CaptureStdout();
    print(cmap);
    EXPECT_EQ(GetCapturedStdout(), "[ {a:1} {b:2} ]\n");

    std::multimap<char,int> cmmap{{'a',1},{'b',2}, {'b',2}};
    CaptureStdout();
    print(cmmap);
    EXPECT_EQ(GetCapturedStdout(), "[ {a:1} {b:2} {b:2} ]\n");

    std::unordered_map<int,std::string> myuomap = {{1,"a"}, {2,"b"}, {3,"c"}};
    CaptureStdout();
    print(myuomap);
    EXPECT_EQ(GetCapturedStdout(), "[ {3:c} {2:b} {1:a} ]\n");

    std::unordered_multimap<int,std::string> myuomap2 = {{1,"a"}, {2,"b"}, {3,"c"}, {1,"a"}, {2,"d"}};
    CaptureStdout();
    print(myuomap2);
    EXPECT_EQ(GetCapturedStdout(), "[ {3:c} {2:d} {2:b} {1:a} {1:a} ]\n");
}

TEST(utillyty_print, stl_pair_and_tuples)
{
    std::pair<int,double> pr {1, 3.14};
    CaptureStdout();
    print(pr);
    EXPECT_EQ(GetCapturedStdout(), "{ 1, 3.14 }\n");

    auto tp = std::make_tuple<int,double,std::string>(1, 4.5, "qwe");
    CaptureStdout();
    print(tp);
    EXPECT_EQ(GetCapturedStdout(), "{ 1, 4.5, qwe }\n");
}

TEST(utillyty_print, custom_inserter)
{
    TestClass mytc;
    CaptureStdout();
    print(mytc);
    EXPECT_EQ(GetCapturedStdout(), "1 | test-class\n\n");
}