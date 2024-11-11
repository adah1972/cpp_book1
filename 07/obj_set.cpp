#include <array>     // std::array
#include <iostream>  // std::cout
#include <set>       // std::set

using namespace std;

template <typename IdType>
struct id_compare {
    template <typename T, typename U>
    bool operator()(const T& lhs, const U& rhs) const
    {
        return lhs.id < rhs.id;
    }
    template <typename T>
    bool operator()(const T& lhs, IdType rhs_id) const
    {
        return lhs.id < rhs_id;
    }
    template <typename T>
    bool operator()(IdType lhs_id, const T& rhs) const
    {
        return lhs_id < rhs.id;
    }

    typedef void is_transparent;
};

struct Obj {
    int id;
    std::array<char, 20> other_info;
};

int main()
{
    set<Obj, id_compare<int>> s{{1, {}}, {2, {}}};
    cout << 1 << ": "
         << (s.find(1) != s.end() ? "FOUND" : "NOT found") << '\n';
    cout << 0 << ": "
         << (s.find(0) != s.end() ? "FOUND" : "NOT found") << '\n';
}
