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

    // Char / string
    char d = 'A';
    print(d);
    const char *e = "asd";
    print(e);
    std::string s = "at";
    print(s);
    print("message");

    // Containers
    std::vector<int> ivec {1,2,3,4,5};
    std::vector<std::string> svec {"asd","zxc","qwe"};
    std::list<int> ilist {2,4,6,8};
    std::forward_list<int> iflist {5,6,7,8};
    std::deque<int> idq {10,11,12,13};
    std::set<int> iset {20,30,40,50,60};
    std::multiset<int> imset {20,30,40,40,40,50,60};

    print(ivec);
    print(svec);
    print(ilist);
    print(iflist);
    print(idq);
    print(iset);
    print(imset);

    // Range-based
    print(ivec.begin(), ivec.end());
    print(svec.begin(), svec.end());
    print(ilist.begin(), ilist.end());
    print(iflist.begin(), iflist.end());
    print(idq.begin(), idq.end());
    print(iset.begin(), iset.end());
    print(imset.begin(), imset.end());
}
