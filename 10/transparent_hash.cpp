#include <cstddef>        // std::size_t
#include <functional>     // std::equal_to/hash
#include <iostream>       // std::cout
#include <string>         // std::string
#include <string_view>    // std::string_view
#include <unordered_set>  // std::unordered_set

struct MyStrHash {
    using is_transparent = void;
    std::size_t operator()(std::string_view str) const noexcept
    {
        return std::hash<std::string_view>{}(str);
    }
};

int main()
{
    using namespace std;
    cout << boolalpha;
    unordered_set<string, MyStrHash, equal_to<>> s{
        "one", "two", "three"};
    cout << s.contains("one")<< '\n';
    cout << s.contains("two")<< '\n';
    cout << s.contains("tres")<< '\n';
}
