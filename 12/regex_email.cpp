#include <iostream>  // std::cout
#include <regex>     // std::regex/regex_match/smatch
#include <string>    // std::string/getline

using namespace std;

int main()
{
    string line;
    regex pat(R"(\w+([.%+-]?\w+)*@\w+([.-]?\w+)*\.\w{2,})");

    for (;;) {
        getline(cin, line);
        if (!cin) {
            break;
        }
        smatch matches;
        auto it = line.cbegin();
        auto ite = line.cend();
        while (regex_search(it, ite, matches, pat)) {
            cout << matches[0] << '\n';
            it = matches.suffix().first;
        }
    }
}
