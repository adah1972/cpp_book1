#include <algorithm>        // std::ranges::sort
#include <functional>       // std::less
#include <iostream>         // std::cout
#include <string_view>      // std::string_view
#include <utility>          // std::pair
#include "ostream_range.h"  // operator<< for ranges

int main()
{
    using namespace std;
    using MyPair = pair<int, string_view>;
    MyPair a[]{{1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}};
#if __cpp_lib_ranges >= 201911L
    using std::ranges::sort;
    sort(a, less{}, &MyPair::second);
#else
    sort(begin(a), end(a),
         [](const MyPair& lhs, const MyPair& rhs) {
             return lhs.second < rhs.second;
         });
#endif
    cout << a << '\n';
}
