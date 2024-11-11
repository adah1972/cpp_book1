#ifndef STRING_HPP
#define STRING_HPP

#include <string.h>  // memcmp/memcpy/strlen/size_t

class String {
public:
    String() : ptr_(nullptr), len_(0) {}
    String(const char* s) : ptr_(nullptr), len_(strlen(s))
    {
        if (len_ != 0) {
            ptr_ = new char[len_ + 1];
            memcpy(ptr_, s, len_ + 1);
        }
    }
    String(const String& rhs) : ptr_(nullptr), len_(rhs.len_)
    {
        if (len_ != 0) {
            ptr_ = new char[rhs.len_ + 1];
            memcpy(ptr_, rhs.ptr_, len_ + 1);
        }
    }
    String& operator=(const String& rhs)
    {
        if (this != &rhs) {
            char* ptr = nullptr;
            if (rhs.len_ != 0) {
                ptr = new char[rhs.len_ + 1];
                memcpy(ptr, rhs.ptr_, len_ + 1);
            }
            delete[] ptr_;
            ptr_ = ptr;
            len_ = rhs.len_;
        }
        return *this;
    }
    ~String()
    {
        delete[] ptr_;
    }

    const char* c_str() const
    {
        return ptr_;
    }
    size_t size() const
    {
        return len_;
    }

    void assign(const char* s);

    static bool equals(const String& lhs, const String& rhs)
    {
        if (lhs.len_ != rhs.len_) {
            return false;
        }
        return memcmp(lhs.ptr_, rhs.ptr_, lhs.len_) == 0;
    }

private:
    char*  ptr_;
    size_t len_;
};

inline void String::assign(const char* s)
{
    size_t len = strlen(s);
    char* ptr = nullptr;
    if (len != 0) {
        ptr = new char[len + 1];
        memcpy(ptr, s, len + 1);
    }
    delete[] ptr_;
    ptr_ = ptr;
    len_ = len;
}

inline bool operator==(const String& lhs, const String& rhs)
{
    return String::equals(lhs, rhs);
}

#endif // STRING_HPP
