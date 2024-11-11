#include <iostream>  // std::cout
#include <vector>    // std::vector

using namespace std;

template <typename C>
void reverseOutput(const C& c)
{
    for (auto it = c.end(); it != c.begin();) {
        --it;
        cout << *it << ' ';
    }
    cout << '\n';

    for (auto it = c.rbegin(); it != c.rend(); ++it) {
        cout << *it << ' ';
    }
    cout << '\n';
}

int main()
{
    vector<int> v{1, 2, 3, 4, 5};
    reverseOutput(v);
}
