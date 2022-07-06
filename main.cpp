#include "utillyty.h"
#include <string>
#include <vector>
#include <list>

using namespace illy;

int main()
{


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
    std::array ar{5,4,3,2,1};

    print(ivec);
    print(svec);
    print(ilist);
    print(iflist);
    print(idq);
    print(iset);
    print(imset);
    print(ar);

    // Range-based
    print(ivec.begin(), ivec.end());
    print(svec.begin(), svec.end());
    print(ilist.begin(), ilist.end());
    print(iflist.begin(), iflist.end());
    print(idq.begin(), idq.end());
    print(iset.begin(), iset.end());
    print(imset.begin(), imset.end());
    print(ar.begin(), ar.end());

    // C-array
    int ca[5] = {1,2,3};
    print(ca);

    // Unordered
    std::unordered_map<int,std::string> myuomap = {{1,"a"}, {2,"b"}, {3,"c"}};
    std::unordered_multimap<int,std::string> myuomap2 = {{1,"a"}, {2,"b"}, {3,"c"}, {1,"a"}, {2,"d"}};
    std::unordered_set<int> myuoset = {23,45,23,45};
    std::unordered_multiset<int> myuoset2 = {23,45,23,45};

    print(myuoset);
    print(myuoset2);
    print(myuomap);
    print(myuomap2);
}
