#include <iostream>         // std::cout
#include <map>              // std::map
#include <ranges>           // std::views::*
#include <string>           // std::string
#include "ostream_range.h"  // operator<< for ranges

int main()
{
    std::map<int, std::string> mp{
        {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}};
    std::cout << (mp | std::views::reverse
                     | std::views::filter([](const auto& pr) {
                           return pr.first % 2 == 0;
                       })
                     | std::views::values)
              << '\n';
}
