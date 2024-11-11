#include <iostream>         // std::cout
#include <set>              // std::set
#include "ostream_range.h"  // operator<< for ranges

using namespace std;

int main()
{
    set<int> s{1, 2, 3, 4, 5, 6, 7, 8};
    cout << "Original set: " << s << '\n';

#if __cpp_lib_erase_if >= 202002L
    erase_if(s, [](int n) { return n % 2 != 0; });
#else
    for (auto it = s.begin(); it != s.end();) {
        if (*it % 2 != 0) {
            it = s.erase(it);
        } else {
            ++it;
        }
    }
#endif
    cout << "Filtered set: " << s << '\n';
}
