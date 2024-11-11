#include <iostream>  // std::cout
#include <iterator>  // std::input_iterator_tag
#include <ranges>    // std::views::*
#include <tuple>     // std::tie/tuple
#include <stddef.h>  // ptrdiff_t
#include <stdint.h>  // uint64_t

class fibonacci {
public:
    class sentinel;
    class iterator;
    iterator begin() noexcept;
    sentinel end() noexcept;
};

class fibonacci::sentinel {};

class fibonacci::iterator {
public:
    typedef ptrdiff_t difference_type;
    typedef uint64_t value_type;
    typedef const uint64_t* pointer;
    typedef const uint64_t& reference;
    typedef std::input_iterator_tag iterator_category;

    value_type operator*() const { return b_; }
    pointer operator->() const { return &b_; }
    iterator& operator++()
    {
        std::tie(a_, b_) = std::tuple(b_, a_ + b_);
        return *this;
    }
    iterator operator++(int)
    {
        auto tmp = *this;
        ++*this;
        return tmp;
    }
    bool operator==(const sentinel&) const { return false; }
    bool operator!=(const sentinel&) const { return true; }

private:
    uint64_t a_{0};
    uint64_t b_{1};
};

inline bool operator==(const fibonacci::sentinel& lhs,
                       const fibonacci::iterator& rhs)
{
    return rhs == lhs;
}
inline bool operator!=(const fibonacci::sentinel& lhs,
                       const fibonacci::iterator& rhs)
{
    return rhs != lhs;
}

inline fibonacci::iterator fibonacci::begin() noexcept
{
    return iterator();
}

inline fibonacci::sentinel fibonacci::end() noexcept
{
    return sentinel();
}

namespace std::ranges {

template <>
inline constexpr bool enable_borrowed_range<fibonacci> = true;

} // namespace std::ranges

namespace views = std::views;
using std::cout;

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
