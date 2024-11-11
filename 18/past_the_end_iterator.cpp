#include <iostream>  // std::cout
#include <string>    // std::string
#include <vector>    // std::vector

using namespace std;

int main()
{
    cout << boolalpha;

    string s{"Hello"};
    cout << "(*s.end() == '\\0'): " << (*s.end() == '\0') << '\n';

    vector v{1, 2, 3};
    cout << "*v.end() = " << *v.end() << '\n';
}

// MSVC can capture both past-the-end dereferences in debug builds.
//
// Clang/libc++ can capture both past-the-end dereferences by defining the
// macro _LIBCPP_DEBUG (to 1).
//
// GCC/libstdc++ can capture the second dereference (only) by defining the
// macro _GLIBCXX_DEBUG.  This is by design:
//   https://gcc.gnu.org/onlinedocs/libstdc++/manual/debug_mode_design.html
