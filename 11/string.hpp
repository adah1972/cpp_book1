#ifndef STRING_HPP
#define STRING_HPP

#include <memory>    // std::unique_ptr/make_unique
#include <utility>   // std::swap
#include <string.h>  // memcmp/memcpy/strlen/size_t

using namespace std;

class String {
public:
    String() : len_(0) {}
    String(const char* s) : len_(strlen(s))
    {
        if (len_ != 0) {
            ptr_ = make_unique<char[]>(len_ + 1);
            memcpy(ptr_.get(), s, len_ + 1);
        }
    }
    String(const String& rhs) : len_(rhs.len_)
    {
        if (len_ != 0) {
            ptr_ = make_unique<char[]>(len_ + 1);
            memcpy(ptr_.get(), rhs.ptr_.get(), len_ + 1);
        }
    }
    String(String&& rhs) noexcept
        : ptr_(std::move(rhs.ptr_)), len_{rhs.len_}
    {
        rhs.len_ = 0;
    }
    String& operator=(const String& rhs)
    {
        String(rhs).swap(*this);
        return *this;
    }
    String& operator=(String&& rhs) noexcept
    {
        String(std::move(rhs)).swap(*this);
        return *this;
    }
    ~String() = default;

    void swap(String& rhs) noexcept
    {
        using std::swap;
        swap(ptr_, rhs.ptr_);
        swap(len_, rhs.len_);
    }

    const char* c_str() const
    {
        return ptr_.get();
    }
    size_t size() const
    {
        return len_;
    }

    void assign(const char* s)
    {
        this->operator=(String(s));
    }

    static bool equals(const String& lhs, const String& rhs)
    {
        if (lhs.len_ != rhs.len_) {
            return false;
        }
        return memcmp(lhs.ptr_.get(), rhs.ptr_.get(), lhs.len_) == 0;
    }

private:
    std::unique_ptr<char[]> ptr_;
    size_t len_;
};

inline bool operator==(const String& lhs, const String& rhs)
{
    return String::equals(lhs, rhs);
}

#endif // STRING_HPP
