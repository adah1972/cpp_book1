#include <iostream>  // std::cout

using namespace std;

int add2(int x)
{
    return x + 2;
};

template <typename T>
auto test1(T fn)
{
    return fn(2);
}

template <typename T>
auto test2(T& fn)
{
    return fn(2);
}

template <typename T>
auto test3(T* fn)
{
    return (*fn)(2);
}

int main()
{
    cout << test1(add2) << '\n';
    cout << test2(add2) << '\n';
    cout << test3(add2) << '\n';
}
