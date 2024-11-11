#include <functional>       // std::greater
#include <iostream>         // std::cout/endl
#include <memory>           // std::pair
#include <queue>            // std::priority_queue
#include <vector>           // std::vector
#include "ostream_range.h"  // operator<< for ranges

using namespace std;

int main()
{
    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<>>
        q;
    q.emplace(1, 1);
    q.emplace(2, 2);
    q.emplace(0, 3);
    q.emplace(9, 4);
    while (!q.empty()) {
        cout << q.top() << endl;
        q.pop();
    }
}
