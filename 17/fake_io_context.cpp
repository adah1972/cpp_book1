#include "fake_io_context.h"  // asio::io_context (fake)
#include <chrono>             // std::chrono_literals
#include <iostream>           // std::cout
#include <thread>             // std::this_thread::sleep_for
#include <vector>             // std::vector
#include "scoped_thread.h"    // scoped_thread

namespace this_thread = std::this_thread;
using namespace std::chrono_literals;
using std::cout;
using std::vector;

asio::io_context context;

void doA();
void doB();
void doC(const int& n);

void doA()
{
    cout << "doA starts\n";
    int answer = 42;
    post(context, doB);
    post(context, [answer] { doC(answer); });
    cout << "doA ends\n";
}

void doB()
{
    cout << "doB starts\n";
    this_thread::sleep_for(10ms);
    cout << "doB ends\n";
}

void doC(const int& n)
{
    cout << "doC starts with " << n << " \n";
    this_thread::sleep_for(10ms);
    cout << "doC ends\n";
}

int main()
{
    post(context, doA);
    vector<scoped_thread> threads;
    threads.emplace_back([] { context.run(); });
    threads.emplace_back([] { context.run(); });
}
