#include <iostream>  // std::cout

#if __cplusplus >= 202002L
#include <algorithm> // std::ranges::for_each
#endif

using std::cout;

struct null_sentinel {};

template <typename I>
bool operator==(I i, null_sentinel)
{
    return *i == 0;
}

template <typename I>
bool operator==(null_sentinel, I i)
{
    return *i == 0;
}

template <typename I>
bool operator!=(I i, null_sentinel)
{
    return *i != 0;
}

template <typename I>
bool operator!=(null_sentinel, I i)
{
    return *i != 0;
}

class c_string_reader {
public:
    c_string_reader(const char* s) : ptr_(s) {}
    const char* begin() const { return ptr_; }
    null_sentinel end() const { return {}; }

private:
    const char* ptr_;
};

int main()
{
    const char* msg = "Hello world!\n";

    for (auto ptr = msg; ptr != null_sentinel{}; ++ptr) {
        cout << *ptr;
    }

    for (char ch : c_string_reader(msg)) {
        cout << ch;
    }

#if __cplusplus >= 202002L
    std::ranges::for_each(msg, null_sentinel{},
                          [](char ch) { cout << ch; });
#endif
}
