#include <cstddef>
#include <vector>

using namespace std;

template <typename T>
struct traits {
    typedef typename T::const_iterator const_iterator;
    static const_iterator begin(const T& c)
    {
        return c.begin();
    }
    static const_iterator end(const T& c)
    {
        return c.end();
    }
};

template <typename T, size_t N>
struct traits<T[N]> {
    typedef const T* const_iterator;
    static const_iterator begin(const T (&a)[N])
    {
        return a;
    }
    static const_iterator end(const T (&a)[N])
    {
        return a + N;
    }
};

template <typename T>
void foo(const T& c)
{
    for (typename traits<T>::const_iterator
             it = traits<T>::begin(c),
             end = traits<T>::end(c);
         it != end; ++it) {
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
