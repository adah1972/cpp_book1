#include <filesystem>    // std::filesystem::*
#include <iostream>      // std::cout
#include <system_error>  // std::errc/error_code

void printError(std::ostream& os, const std::error_code& ec,
                const char* end = "")
{
    os << ec.category().name() << ": " << ec.message() << end;
}

using std::cout;
using std::errc;
using std::error_code;

int main()
{
    namespace fs = std::filesystem;
    fs::path path{"abcdef/example"};

    // 方法一
    try {
        bool result = fs::remove(path);
        cout << "remove " << (result ? "succeeded" : "failed")
             << "!\n";
    }
    catch (const fs::filesystem_error& e) {
        cout << "remove failed with exception!\n";
        cout << e.what() << '\n';
        if (e.code() == errc::permission_denied) {
            cout << "Please check permission!\n";
        }
    }

    // 方法二
    error_code ec;
    if (fs::remove(path, ec)) {
        cout << "remove succeeded!\n";
    } else {
        cout << "remove failed";
        if (ec) {
            cout << " with error!\n";
            printError(cout, ec, "\n");
            if (ec == errc::permission_denied) {
                cout << "Please check permission!\n";
            }
        } else {
            cout << "!\n";
        }
    }
}
