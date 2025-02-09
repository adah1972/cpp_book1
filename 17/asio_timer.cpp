#include <iostream>      // std::cout
#include <memory>        // std::make_shared
#include <system_error>  // std::error_code
#include "asio.h"        // asio::*

using namespace std::chrono_literals;
using std::cout;
using std::make_shared;

asio::io_context context;

void sayHello()
{
    cout << "Hello, world!\n";
}

void doA()
{
    cout << "doA starts\n";
    auto t = make_shared<asio::steady_timer>(context, 2s);
    t->async_wait([t](const error_code& ec) {
        if (ec == asio::error::operation_aborted) {
            return;
        }
        sayHello();
    });

    //t->cancel();
    cout << "doA ends\n";
}

int main()
{
    post(context, doA);
    context.run();
}
