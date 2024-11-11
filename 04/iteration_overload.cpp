#include <cstddef>
#include <vector>

using namespace std;

template <typename C>
void foo(const C& c)
{
    for (typename C::const_iterator it = c.begin(), end = c.end();
         it != end; ++it) {
        // 循环体
    }
}

template <typename T, size_t N>
void foo(const T (&a)[N])
{
    typedef const T* ptr_t;
    for (ptr_t it = a, end = a + N; it != end; ++it) {
        // 循环体
    }
}

int main()
{
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    foo(v);
    int a[] = {1, 2, 3};
    foo(a);
}
