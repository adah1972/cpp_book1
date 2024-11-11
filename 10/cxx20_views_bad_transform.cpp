#include <iostream>         // std::cout
#include <map>              // std::map
#include <ranges>           // std::views::*
#include <string>           // std::string
#include "ostream_range.h"  // operator<< for ranges

int main()
{
    std::map<int, std::string> mp{
        {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}};
    int tf_count{};
    std::cout << (mp | std::views::transform([&tf_count](const auto& pr) {
                           ++tf_count;
                           return pr.first;
                       })
                     | std::views::filter([](int num) {
                           return num % 2 == 0;
                       }))
              << '\n';
    std::cout << tf_count << " transformations are made\n";
}
