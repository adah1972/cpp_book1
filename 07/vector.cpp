#include <iostream>  // std::cout
#include <vector>    // std::vector
#include <stddef.h>  // size_t

using namespace std;

int main()
{
    vector<int> v{1, 2, 3, 4};
    v.push_back(5);
    v.insert(v.begin(), 0);
    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i] << ' ';
    }
    cout << '\n';

    int sum = 0;
    for (auto it = v.begin(); it != v.end(); ++it) {
        sum += *it;
    }
    cout << sum << '\n';
}
