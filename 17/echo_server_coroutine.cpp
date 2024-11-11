#include <exception>  // std::exception
#include <iostream>   // std::cerr
#include <utility>    // std::move
#include <stddef.h>   // size_t
#include "asio.h"     // asio::*

using asio::awaitable;
using asio::buffer;
using asio::co_spawn;
using asio::detached;
using asio::use_awaitable;
using asio::ip::tcp;
using std::cerr;
using std::exception;

#if defined(BOOST_ASIO_ENABLE_HANDLER_TRACKING)
#define use_awaitable                                                      \
    use_awaitable_t(__FILE__, __LINE__, __PRETTY_FUNCTION__)
#endif

awaitable<void> processConnection(tcp::socket socket)
{
    char data[1024];
    for (;;) {
        error_code ec;
        size_t len = co_await socket.async_read_some(
            buffer(data), redirect_error(use_awaitable, ec));
        if (ec) {
            if (ec == asio::error::eof) {
                cerr << "Session done\n";
            } else {
                cerr << "Error: " << ec.message() << "\n";
            }
            break;
        }
        co_await async_write(
            socket, buffer(data, len),
            redirect_error(use_awaitable, ec));
        if (ec) {
            cerr << "Error: " << ec.message() << "\n";
            break;
        }
    }
}

awaitable<void> listener()
{
    try {
        auto executor = co_await asio::this_coro::executor;
        tcp::acceptor acceptor(executor,
                               tcp::endpoint(tcp::v4(), 6667));
        int count{};
        for (;;) {
            tcp::socket socket =
                co_await acceptor.async_accept(use_awaitable);
            co_spawn(executor,
                     processConnection(std::move(socket)),
                     detached);
            if (++count == 1000) {
                break;
            }
        }
    }
    catch (const exception& e) {
        cerr << "Exception: " << e.what() << "\n";
    }
}

int main()
{
    try {
        asio::io_context context(1);
        co_spawn(context, listener, detached);
        context.run();
    }
    catch (const exception& e) {
        cerr << "Exception: " << e.what() << "\n";
    }
}
