#include "utillyty.h"
#include <string>
#include <vector>
#include <list>
#include <variant>
//#include <ostream>

using namespace illy;

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

int main()
{
    /* Overload pattern test */
    illy::overload identifier_func {
        [](int) {return "visiting with integer.";},
        [](std::string) {return "visiting with string.";},
        [](float) {return "visiting with float.";},
    };

    std::variant<int, std::string, float> var;

    var = 11;
    print(std::visit(identifier_func, var));
    var = "horse";
    print(std::visit(identifier_func, var));
    var = 12.4f;
    print(std::visit(identifier_func, var));

    print(identifier_func(5));
    print(identifier_func(5.3f));
    print(identifier_func("asd"));

    /* Basic testing */
    // Primitives
    print(10);
    print(4.5);
    print(6.32f);
    int a = 5;
    print(a);
    double b = 3.14;
    print(b);
    float c = 1.001;
    print(c);

    // Char & string
    char d = 'A';
    print(d);
    const char *e = "asd";
    print(e);
    std::string s = "at";
    print(s);
    print("message");

    // Container adaptors
    std::stack<int> mstack{};
    mstack.push(100);
    mstack.push(101);
    mstack.push(102);
    print(mstack);
    print(mstack);

    std::queue<int> mqueue{};
    mqueue.push(200);
    mqueue.push(201);
    mqueue.push(202);
    print(mqueue);
    print(mqueue);

    std::priority_queue<int> mpqueue{};
    mpqueue.push(300);
    mpqueue.push(301);
    mpqueue.push(302);
    print(mpqueue);
    print(mpqueue);

    // Containers
    std::vector<int> ivec {1,2,3,4,5};
    std::vector<std::string> svec {"asd","zxc","qwe"};
    std::list<int> ilist {2,4,6,8};
    std::forward_list<int> iflist {5,6,7,8};
    std::deque<int> idq {10,11,12,13};
    std::set<int> iset {20,30,40,50,60};
    std::multiset<int> imset {20,30,40,40,40,50,60};
    std::array arr {5,4,3,2,1};

    print(ivec);
    print(svec);
    print(ilist);
    print(iflist);
    print(idq);
    print(iset);
    print(imset);
    print(arr);

    // Range-based
    print(ivec.begin(), ivec.end());
    print(svec.begin(), svec.end());
    print(ilist.begin(), ilist.end());
    print(iflist.begin(), iflist.end());
    print(idq.begin(), idq.end());
    print(iset.begin(), iset.end());
    print(imset.begin(), imset.end());
    print(arr.begin(), arr.end());

    // C-array
    int ca[5] = {1,2,3};
    print(ca);

    // Maps
    std::map<char,int> cmap{{'a',1},{'b',2}};
    std::multimap<char,int> cmmap{{'a',1},{'b',2}, {'b',2}};
    print(cmap);
    print(cmmap);

    // Unordered Maps
    std::unordered_map<int,std::string> myuomap = {{1,"a"}, {2,"b"}, {3,"c"}};
    std::unordered_multimap<int,std::string> myuomap2 = {{1,"a"}, {2,"b"}, {3,"c"}, {1,"a"}, {2,"d"}};
    std::unordered_set<int> myuoset = {23,45,23,45};
    std::unordered_multiset<int> myuoset2 = {23,45,23,45};

    print(myuoset);
    print(myuoset2);
    print(myuomap);
    print(myuomap2);

    // Pair and Tuple
    std::pair<int,double> pr {1, 3.14};
    print(pr);

    auto tp = std::make_tuple<int,double,std::string>(1, 4.5, "qwe");
    print(tp);

    // Custom class with inserter
    TestClass mytc;
    print(mytc);
}
