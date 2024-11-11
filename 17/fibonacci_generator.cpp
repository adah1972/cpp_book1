#include <iostream>               // std::cout
#include <tuple>                  // std::tie/tuple
#include <ranges>                 // std::views::*
#include <version>                // __cpp_lib_generator
#include <stdint.h>               // uint64_t

#if __cpp_lib_generator >= 202207L
#include <generator>              // std::generator
using std::generator;
#elif __has_include(<cppcoro/generator.hpp>)
#include <cppcoro/generator.hpp>  // cppcoro::generator
using cppcoro::generator;
#else
#error "No generator suport is detected"
#endif

namespace views = std::views;
using std::cout;

generator<uint64_t> fibonacci()
{
    uint64_t a = 0;
    uint64_t b = 1;
    for (;;) {
        co_yield b;
        std::tie(a, b) = std::tuple(b, a + b);
    }
}

int main()
{
    for (auto i : fibonacci() | views::take(20)) {
        cout << i << '\n';
    }
    for (auto i : fibonacci() | views::take_while([](uint64_t n) {
                      return n < 10000;
                  })) {
        cout << i << '\n';
    }
    for (auto i : fibonacci() | views::drop_while([](uint64_t n) {
                      return n < 10000;
                  })) {
        cout << i << '\n';
        break;
    }
}
