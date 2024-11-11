#include <algorithm>        // std::generate/iota/shuffle
#include <array>            // std::array
#include <cstdint>          // std::uint32_t
#include <iostream>         // std::cout
#include <random>           // std::mt19937/random_device/seed_seq
#include <vector>           // std::vector
#include "ostream_range.h"  // operator<< for ranges

using namespace std;

int main()
{
    random_device rd;
    array<uint32_t, 4> seeds{};
    generate(seeds.begin(), seeds.end(), [&] { return rd(); });
    cout << "Seeds are " << seeds << '\n';
    seed_seq sq(seeds.begin(), seeds.end());
    mt19937 engine{sq};
    vector<int> v(54);
    iota(v.begin(), v.end(), 1);
    shuffle(v.begin(), v.end(), engine);
    cout << v << '\n';
}
