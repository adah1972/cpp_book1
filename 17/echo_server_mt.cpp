#include <exception>  // std::exception
#include <iostream>   // std::cerr
#include <thread>     // std::thread
#include <utility>    // std::move
#include <stddef.h>   // size_t
#include "asio.h"     // asio::*

using asio::buffer;
using asio::ip::tcp;
using std::cerr;
using std::exception;
using std::thread;

void processConnection(tcp::socket peer)
{
    char data[1024];
    for (;;) {
        error_code ec;
        size_t len = peer.read_some(buffer(data), ec);
        if (ec) {
            if (ec == asio::error::eof) {
                cerr << "Session done\n";
            } else {
                cerr << "Error: " << ec.message() << "\n";
            }
            break;
        }
        write(peer, buffer(data, len), ec);
        if (ec) {
            cerr << "Error: " << ec.message() << '\n';
            break;
        }
    }
}

int main()
{
    asio::io_context context;
    try {
        tcp::acceptor acceptor(
            context, tcp::endpoint(tcp::v4(), 6667));

        for (;;) {
            tcp::socket peer(context);
            acceptor.accept(peer);
            thread(processConnection, std::move(peer)).detach();
        }
    }
    catch (const exception& e) {
        cerr << "Exception: " << e.what() << "\n";
    }
}
