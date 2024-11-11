#include <iostream>  // std::cout
#include <regex>     // std::regex/regex_match/smatch
#include <string>    // std::string/getline

using namespace std;

int main()
{
    string line;
    regex pat(R"(\w+([.%+-]?\w+)*@\w+([.-]?\w+)*\.\w{2,})");

    while (cin) {
        getline(cin, line);
        sregex_iterator pos(line.cbegin(), line.cend(), pat);
        sregex_iterator end;
        for (; pos != end; ++pos) {
            cout << (*pos)[0] << '\n';
        }
    }
}
