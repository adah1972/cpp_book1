#include <algorithm>  // std::copy/sort
#include <iostream>   // std::cout
#include <iterator>   // std::ostream_iterator

int main()
{
    using namespace std;
    int a[] = {1, 7, 3, 6, 5, 2, 4, 8};
    copy(begin(a), end(a), ostream_iterator<int>(cout, " "));
    cout << '\n';
    sort(begin(a), end(a));
    copy(begin(a), end(a), ostream_iterator<int>(cout, " "));
    cout << '\n';
}
