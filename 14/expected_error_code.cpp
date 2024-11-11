#include <climits>          // INT_MAX/INT_MIN
#include <ios>              // std::boolalpha
#include <iostream>         // std::cout/endl
#include <ostream>          // std::ostream
#include <string>           // std::string
#include <system_error>     // std::errc/error_code/error_condition/...
#include <type_traits>      // std::true_type

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

template <>
struct std::is_error_code_enum<DivErrc> : true_type {
};

class DivErrcCategory : public std::error_category {
public:
    const char* name() const noexcept override
    {
        return "divide error";
    }
    std::string message(int c) const override
    {
        switch (static_cast<DivErrc>(c)) {
        case DivErrc::success:
            return "Successful";
        case DivErrc::divide_by_zero:
            return "Divide by zero";
        case DivErrc::integer_divide_overflows:
            return "Integer divide overflows";
        case DivErrc::not_integer_division:
            return "Not integer division";
        }
        return "Unknown";
    }
    // Optional: Allow generic error conditions to be compared
    std::error_condition
    default_error_condition(int c) const noexcept override
    {
        switch (static_cast<DivErrc>(c)) {
        case DivErrc::success:
            break;
        case DivErrc::divide_by_zero:
            return {std::errc::invalid_argument};
        case DivErrc::integer_divide_overflows:
            return {std::errc::value_too_large};
        case DivErrc::not_integer_division:
            return {std::errc::result_out_of_range};
        }
        return {c, *this};
    }
};

std::error_code make_error_code(DivErrc e)
{
    static DivErrcCategory category;
    return {static_cast<int>(e), category};
}

expected<int, std::error_code> divideSafe(int i, int j)
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

expected<int, std::error_code> addDivideSafe(int i, int j, int k)
{
    return divideSafe(j, k).and_then(
        [i](int q) -> expected<int, std::error_code> {
            if ((i > 0 && q > INT_MAX - i) ||
                (i < 0 && q < INT_MIN - i)) {
                return unexpected(
                    make_error_code(std::errc::value_too_large));
            }
            return i + q;
        });
}

void printError(std::ostream& os, const std::error_code& ec,
                const char* end = "")
{
    os << ec.category().name() << ": " << ec.message() << end;
}

void printError(std::ostream& os, const std::error_condition& ec,
                const char* end = "")
{
    os << ec.category().name() << ": " << ec.message() << end;
}

std::ostream& operator<<(std::ostream& os,
                         const expected<int, std::error_code>& exp)
{
    if (exp) {
        os << *exp;
    } else {
        printError(os, exp.error());
    }
    return os;
}

void check(const expected<int, std::error_code>& result)
{
    std::cout << result;
    if (!result && result.error() == DivErrc::divide_by_zero) {
        std::cout << ": Are you serious?";
    } else if (result && *result == 42) {
        std::cout << ": Ha, I got you!";
    }
    std::cout << std::endl;
}

int main()
{
    std::cout << "*** Error code test\n";
    printError(std::cout, std::errc::address_not_available, "\n");
    printError(std::cout, DivErrc(10), "\n");
    printError(std::cout, DivErrc::divide_by_zero, "\n");
    std::cout << std::boolalpha
              << (make_error_code(DivErrc::divide_by_zero) ==
                  std::errc::invalid_argument)
              << std::endl;
    std::cout << "*** Expected test\n";
    check(addDivideSafe(INT_MAX, 2, 2));
    check(addDivideSafe(1, INT_MIN, -1));
    check(addDivideSafe(2, 1, 0));
    check(addDivideSafe(37, 20, 7));
    check(addDivideSafe(39, 21, 7));
}
