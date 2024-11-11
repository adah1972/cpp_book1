#include <algorithm>        // std::copy_n/fill_n
#include <array>            // std::size
#include <cassert>          // assert
#include <iostream>         // std::cout/endl
#include <optional>         // std::optional
#include <stdexcept>        // std::runtime_error
#include <system_error>     // std::errc/error_code/make_error_code

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

using std::copy_n;
using std::cout;
using std::errc;
using std::error_code;
using std::fill_n;
using std::make_error_code;
using std::optional;
using std::size;

class BigObj {
public:
    BigObj() noexcept
    {
        cout << __PRETTY_FUNCTION__ << '\n';
    }
    BigObj(int n) noexcept
    {
        cout << __PRETTY_FUNCTION__ << '\n';
        fill_n(data_, size(data_), n);
    }
    BigObj(const BigObj& rhs) noexcept
    {
        cout << __PRETTY_FUNCTION__ << '\n';
        copy_n(rhs.data_, size(rhs.data_), data_);
    }
    BigObj& operator=(const BigObj& rhs) noexcept
    {
        cout << __PRETTY_FUNCTION__ << '\n';
        if (this != &rhs) {
            copy_n(rhs.data_, size(rhs.data_), data_);
        }
        return *this;
    }
    ~BigObj()
    {
        cout << __PRETTY_FUNCTION__ << '\n';
    }

    void op()
    {
        cout << __PRETTY_FUNCTION__ << '\n';
    }

private:
    int data_[300];
};

struct BigStruct {
    int data[300];
};

BigObj getObj1(bool cond)
{
    if (!cond) {
        throw std::runtime_error("Condition not satisfied");
    }
    BigObj obj{42};
    obj.op();
    return obj;
}

optional<BigObj> getObj2(bool cond)
{
    if (!cond) {
        return {};
    }
    BigObj obj{42};
    obj.op();
    return obj;
}

optional<BigObj> getObj3(bool cond)
{
    optional<BigObj> result;
    if (!cond) {
        return result;
    }
    result.emplace(42);
    result->op();
    return result;
}

expected<BigObj, error_code> getObj4(bool cond)
{
    if (!cond) {
        return unexpected(make_error_code(errc::invalid_argument));
    }
    BigObj obj{42};
    obj.op();
    return obj;
}

expected<BigObj, error_code> getObj5(bool cond)
{
    expected<BigObj, error_code> result{unexpected(error_code{})};
    if (!cond) {
        result =
            unexpected(make_error_code(errc::invalid_argument));
        return result;
    }
    result.emplace(42);
    result->op();
    return result;
}

expected<BigStruct, error_code> getObj6(bool cond)
{
    expected<BigStruct, error_code> result;
    if (!cond) {
        result =
            unexpected(make_error_code(errc::invalid_argument));
        return result;
    }
    assert(result.has_value());
    std::fill_n(result->data, size(result->data), 42);
    return result;
}

int main()  // NOLINT(bugprone-exception-escape)
{
    {
        cout << "*** Return directly w/ RVO\n";
        auto obj = getObj1(true);
    }
    {
        cout << "*** Return optional w/o RVO\n";
        auto obj = getObj2(true);
    }
    {
        cout << "*** Return optional w/ RVO\n";
        auto obj = getObj3(true);
    }
    {
        cout << "*** Return expected w/o RVO\n";
        auto obj = getObj4(true);
    }
    {
        cout << "*** Return expected w/ RVO\n";
        auto obj = getObj5(true);
    }
    {
        auto obj = getObj6(true);
        assert(obj->data[99] == 42);
    }
}
