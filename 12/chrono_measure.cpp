#include <chrono>    // std::chrono::*
#include <iostream>  // std::cout

using namespace std;

int main()
{
    {
        auto t1 = chrono::steady_clock::now();
        cout << "Hello world\n";
        auto t2 = chrono::steady_clock::now();
        cout << (t2 - t1) / 1ns << " ns has elapsed\n";
    }
    {
        auto t1 = chrono::steady_clock::now();
        cout << "Hello world\n";
        auto t2 = chrono::steady_clock::now();
        cout << (t2 - t1) / 1ns << " ns has elapsed\n";
    }
}

