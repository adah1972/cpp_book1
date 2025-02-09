#include <chrono>    // std::chrono_literals
#include <iostream>  // std::cout
#include <thread>    // std::this_thread::sleep_for
#include "asio.h"    // asio::*

namespace this_thread = std::this_thread;
using namespace std::chrono_literals;
using std::cout;

asio::io_context context;

void doA();
void doB();
void doC();

void doA()
{
    cout << "doA starts\n";
    post(context, doB);
    post(context, doC);
    cout << "doA ends\n";
}

void doB()
{
    cout << "doB starts\n";
    this_thread::sleep_for(10ms);
    cout << "doB ends\n";
}

void doC()
{
    cout << "doC starts\n";
    this_thread::sleep_for(10ms);
    cout << "doC ends\n";
}

int main()
{
    post(context, doA);
    context.run();
}
