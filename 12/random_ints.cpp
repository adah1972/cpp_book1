#include <algorithm>        // std::generate
#include <iostream>         // std::cout
#include <random>           // std::mt19937/random_device/...
#include <vector>           // std::vector
#include "ostream_range.h"  // operator<< for ranges

using namespace std;

int main()
{
    auto seed = random_device{}();
    cout << "Seed is " << seed << '\n';
    mt19937 engine{seed};
    uniform_int_distribution dist{1, 1000};
    vector<int> v(100);
    generate(v.begin(), v.end(), [&] { return dist(engine); });
    cout << v << '\n';
}
