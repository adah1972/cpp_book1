#include <exception>  // std::exception
#include <iostream>   // std::cerr
#include <memory>     // std::make_shared/...
#include <utility>    // std::move
#include <stddef.h>   // size_t
#include <stdint.h>   // uint16_t
#include "asio.h"     // asio::*

using asio::buffer;
using asio::ip::tcp;
using std::cerr;
using std::enable_shared_from_this;
using std::exception;
using std::make_shared;

class Session : public enable_shared_from_this<Session> {
public:
    Session(tcp::socket socket) : socket_(std::move(socket)) {}

    void start() { doRead(); }

private:
    void doRead()
    {
        auto self = shared_from_this();
        socket_.async_read_some(
            buffer(data_),
            [this, self](error_code ec, size_t length) {
                if (!ec) {
                    doWrite(length);
                } else if (ec == asio::error::eof) {
                    cerr << "Session done\n";
                } else {
                    cerr << "Error: " << ec.message() << "\n";
                }
            });
    }

    void doWrite(size_t length)
    {
        auto self = shared_from_this();
        asio::async_write(
            socket_, buffer(data_, length),
            [this, self](error_code ec, size_t /*length*/) {
                if (!ec) {
                    doRead();
                } else {
                    cerr << "Error: " << ec.message() << "\n";
                }
            });
    }

    tcp::socket socket_;
    char data_[1024];
};

class Server {
public:
    Server(asio::io_context& context, uint16_t port)
        : acceptor_(context, tcp::endpoint(tcp::v4(), port))
    {
        doAccept();
    }

private:
    void doAccept()
    {
        acceptor_.async_accept([this](error_code ec,
                                      tcp::socket socket) {
            if (!ec) {
                make_shared<Session>(std::move(socket))->start();
            }
            doAccept();
        });
    }

    tcp::acceptor acceptor_;
};

int main()
{
    asio::io_context context(1);
    try {
        Server s(context, 6667);
        context.run();
    }
    catch (const exception& e) {
        cerr << "Exception: " << e.what() << "\n";
    }
}
