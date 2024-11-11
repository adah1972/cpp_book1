#include <algorithm>        // std::sort
#include <iostream>         // std::cout/endl
#include <list>             // std::list
#include <vector>           // std::vector
#include "ostream_range.h"  // operator<< for ranges

using namespace std;

int main()
{
    list<int> lst{1, 7, 2, 8, 3};
    vector<int> vec{1, 7, 2, 8, 3};

    sort(vec.begin(), vec.end());     // 正常
    // sort(lst.begin(), lst.end());  // 不能编译
    lst.sort();                       // 正常

    cout << lst << endl;  // 输出 { 1, 2, 3, 7, 8 }
    cout << vec << endl;  // 输出 { 1, 2, 3, 7, 8 }
}
