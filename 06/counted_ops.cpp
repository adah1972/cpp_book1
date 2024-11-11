#include <functional>  // std::function
#include <iostream>    // std::cout
#include <map>         // std::map

using namespace std;

int main()
{
    int count_plus{};
    int count_minus{};
    int count_multiplies{};
    int count_divides{};

    map<string, function<int(int, int)>> ops{
        {"+",
         [&count_plus](int x, int y) {
             ++count_plus;
             return x + y;
         }},
        {"-",
         [&count_minus](int x, int y) {
             ++count_minus;
             return x - y;
         }},
        {"*",
         [&count_multiplies](int x, int y) {
             ++count_multiplies;
             return x * y;
         }},
        {"/",
         [&count_divides](int x, int y) {
             ++count_divides;
             return x / y;
         }},
    };

    cout << ops.at("+")(ops.at("*")(5, 8), 2) << '\n';
    cout << count_multiplies << '\n';
    cout << count_plus << '\n';
}
