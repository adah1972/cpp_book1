#include <algorithm>  // std::ranges::copy/sort
#include <iostream>   // std::cout
#include <iterator>   // std::ostream_iterator

int main()
{
    using namespace std;
    using std::ranges::copy;
    using std::ranges::sort;
    int a[] = {1, 7, 3, 6, 5, 2, 4, 8};
    copy(a, ostream_iterator<int>(cout, " "));
    cout << '\n';
    sort(a);
    copy(a, ostream_iterator<int>(cout, " "));
    cout << '\n';
}
