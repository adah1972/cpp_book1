#include <iostream>         // std::cout
#include "scoped_thread.h"  // scoped_thread

#define LOOPS 100000

volatile int v;

void increment(volatile int& n)
{
    for (int i = 0; i < LOOPS; ++i) {
        n = n + 1;
    }
}

int main()
{
    {
        scoped_thread t1{increment, std::ref(v)};
        scoped_thread t2{increment, std::ref(v)};
    }
    std::cout << "Result is " << v << std::endl;
}
