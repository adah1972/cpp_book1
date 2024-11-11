#include <functional>       // std::greater
#include <iostream>         // std::cout
#include <map>              // std::map/multimap
#include <set>              // std::set/multiset
#include <string>           // std::string
#include <tuple>            // std::tuple
#include "ostream_range.h"  // operator<< for ranges

using namespace std;

int main()
{
    cout << boolalpha;

    set<int> s{1, 1, 1, 2, 3, 4};
    cout << s << '\n';         // 重复元素被去除
    multiset<int, greater<int>> ms{1, 1, 1, 2, 3, 4};
    cout << ms << '\n';        // 重复元素会保留
    map<string, int> mp{
        {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}
    };
    cout << mp << '\n';
    mp.insert({"four", 4});    // 键已存在，插入无效
    cout << mp << '\n';
    cout << (mp.find("four") != mp.end()) << '\n';
    cout << (mp.find("five") != mp.end()) << '\n';
    mp["five"] = 5;            // 创建或覆盖 "five" 键
    mp.erase("one");           // 删除 "one" 键
    cout << (mp.find("five") != mp.end()) << '\n';
    cout << mp << '\n';
    multimap<string, int> mmp{
        {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}
    };
    mmp.insert({"four", -4});  // 一定插入成功（键可以重复）
    cout << mmp << '\n';

    auto it = mp.find("four");
    if (it != mp.end()) {
        cout << "Found: " << it->second << '\n';
    }
    it = mp.lower_bound("four");
    if (it != mp.end() &&
        !(less<string>{}("four", it->first))) {
        // 后半部分条件此处也可以用更简单的 it->first == "four"
        cout << "Found: " << it->second << '\n';
    }

    multimap<string, int>::iterator lower, upper;
    std::tie(lower, upper) = mmp.equal_range("four");
    if ((lower != upper)) {
        cout << "Found:";
        while (lower != upper) {
            cout << ' ' << lower->second;
            ++lower;
        }
        cout << '\n';
    }
}
