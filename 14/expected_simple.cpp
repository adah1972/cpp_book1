#include <climits>          // INT_MIN
#include <ios>              // std::boolalpha
#include <iostream>         // std::cout/endl
#include <ostream>          // std::ostream

#if __cplusplus > 202002L && __has_include(<expected>)
#include <expected>         // std::expected/unexpected
#endif

#if __cpp_lib_expected >= 202211L
using std::expected;
using std::unexpected;
#elif __has_include(<tl/expected.hpp>)
#include <tl/expected.hpp>  // tl::expected/unexpected
using tl::expected;
using tl::unexpected;
#else
#error "No implementation of expected is found"
#endif

enum class DivErrc {
    success,
    divide_by_zero,
    integer_divide_overflows,
    not_integer_division,
};

expected<int, DivErrc> divideSafe(int i, int j)
{
    if (j == 0) {
        return unexpected(DivErrc::divide_by_zero);
    }
    if (i == INT_MIN && j == -1) {
        return unexpected(DivErrc::integer_divide_overflows);
    }
    if (i % j != 0) {
        return unexpected(DivErrc::not_integer_division);
    }
    return i / j;
}

expected<int, DivErrc> addDivideSafe(int i, int j, int k)
{
    return divideSafe(j, k).and_then(
        [i](int q) -> expected<int, DivErrc> {
            return i + q;
        });
}

expected<int, DivErrc> addDivideSafeVerbose(int i, int j, int k)
{
    auto result = divideSafe(j, k);
    if (!result) {
        return unexpected(result.error());
    }
    auto q = *result;
    return i + q;
}

expected<bool, DivErrc> isQuotient42(int i, int j)
{
    return divideSafe(i, j).and_then(
        [](int q) -> expected<bool, DivErrc> {
            return q == 42;
        });
}

std::ostream& operator<<(std::ostream& os,
                         const expected<int, DivErrc>& exp)
{
    if (exp) {
        os << *exp;
    } else {
        os << "DivErrc: " << int(exp.error());
    }
    return os;
}

void check(const expected<int, DivErrc>& result)
{
    std::cout << result;
    if (!result && result.error() == DivErrc::divide_by_zero) {
        std::cout << ": Are you serious?";
    } else if (result && *result == 42) {
        std::cout << ": Ha, I got you!";
    }
    std::cout << std::endl;
}

void check(const expected<bool, DivErrc>& result)
{
    if (!result) {
        std::cout << "Bad result!" << std::endl;
        return;
    }
    if (*result) {
        std::cout << "Check is successful!" << std::endl;
    } else {
        std::cout << "Check has failed!" << std::endl;
    }
}

int main()
{
    std::cout << "*** Expected test\n";
    check(addDivideSafeVerbose(2, 1, 0));
    check(addDivideSafe(37, 20, 7));
    check(addDivideSafe(39, 21, 7));
    check(isQuotient42(83, 3));
    check(isQuotient42(84, 3));
    check(isQuotient42(84, 2));
}
