#include <exception>  // std::exception
#include <iostream>   // std::cout
#include <string>     // std::string/getline
#include <thread>     // std::thread
#include "asio.h"     // asio::*

using asio::ip::tcp;
using std::cin;
using std::cout;
using std::exception;
using std::getline;
using std::string;
using std::thread;

int main(int argc, char* argv[])
{
    try {
        if (argc != 3) {
            cout << "Usage: " << argv[0] << " <server> <port>\n";
            return 1;
        }

        tcp::iostream s;
        s.connect(argv[1], argv[2]);
        if (!s) {
            cout << "Unable to connect: " << s.error().message()
                 << "\n";
            return 2;
        }

        thread thrd{[&s] { cout << s.rdbuf(); }};

        string line;
        for (;;) {
            getline(cin, line);
            if (!cin) {
                break;
            }
            s << line << "\r\n";
        }

        s.socket().shutdown(tcp::socket::shutdown_send);
        thrd.join();
    }
    catch (const exception& e) {
        cout << "Exception: " << e.what() << "\n";
    }
}
