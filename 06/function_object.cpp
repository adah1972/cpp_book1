#include <functional>  // std::bind/bind2nd/function/plus
#include <iostream>    // std::cout
#include <map>         // std::map
#include <string>      // std::string

using namespace std;

struct Adder {
    Adder(int n) : n_(n) {}
    int operator()(int x) const
    {
        return x + n_;
    }

private:
    int n_;
};

int main()
{
    {
        Adder add2(2);
        cout << "Manual function object: " << add2(5) << '\n';
    }

#if __cplusplus < 201703L
#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif
    {
        auto add2 = bind2nd(plus<int>(), 2);
        cout << "bind2nd: " << add2(5) << '\n';
    }
#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif
#endif

    {
        using namespace std::placeholders;
        // NOLINTNEXTLINE(modernize-avoid-bind)
        auto add2 = bind(plus<int>(), _1, 2);
        cout << "bind: " << add2(5) << '\n';
    }

    {
        auto add2 = [](int x) { return x + 2; };
        cout << "Lambda: " << add2(5) << '\n';
    }

    {
        auto adder = [](int n) { return [n](int x) { return x + n; }; };
        cout << "Currying: " << adder(2)(5) << '\n';
    }

    {
        map<string, function<int(int, int)>> op_dict{
            {"+", [](int x, int y) { return x + y; }},
            {"-", [](int x, int y) { return x - y; }},
            {"*", [](int x, int y) { return x * y; }},
            {"/", [](int x, int y) { return x / y; }},
        };
        cout << "std::function: " << op_dict.at("+")(1, 6) << '\n';
    }
}
