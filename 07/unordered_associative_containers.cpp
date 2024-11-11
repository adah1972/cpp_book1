#include <iostream>         // std::cout
#include <string>           // std::string
#include <tuple>            // std::tuple
#include <unordered_map>    // std::unordered_map/unordered_multimap
#include <unordered_set>    // std::unordered_set/unordered_multiset
#include "ostream_range.h"  // operator<< for ranges

using namespace std;

int main()
{
    cout << boolalpha;

    unordered_set<int> s{1, 1, 1, 2, 3, 4};
    cout << s << '\n';         // 重复元素被去除
    unordered_multiset<int> ms{1, 1, 1, 2, 3, 4};
    cout << ms << '\n';        // 重复元素会保留
    unordered_map<string, int> mp{
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
    unordered_multimap<string, int> mmp{
        {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}
    };
    mmp.insert({"four", -4});  // 一定插入成功（键可以重复）
    cout << mmp << '\n';

    auto it = mp.find("four");
    if (it != mp.end()) {
        cout << "Found: " << it->second << '\n';
    }

    unordered_multimap<string, int>::iterator lower, upper;
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
