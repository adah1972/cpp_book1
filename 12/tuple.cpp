#include <algorithm>  // std::sort
#include <iostream>   // std::cout
#include <string>     // std::string
#include <tuple>      // std::tuple
#include <vector>     // std::vector

using namespace std;

using num_tuple = tuple<int, string, string>;

ostream& operator<<(ostream& os, const num_tuple& value)
{
    os << get<0>(value) << ',' << get<1>(value) << ','
       << get<2>(value);
    return os;
}

int main()
{
    cout << "Tuple size is " << tuple_size_v<num_tuple> << '\n';
    vector<num_tuple> vn{
        {1, "one", "un"},
        {2, "two", "deux"},
        {3, "three", "trois"},
        {4, "four", "quatre"},
    };
    get<2>(vn[0]) = "une";
    sort(vn.begin(), vn.end(),
         [](auto& x, auto& y) { return get<2>(x) < get<2>(y); });
    for (const auto& value : vn) {
        cout << value << '\n';
    }
}
