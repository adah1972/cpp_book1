#include <chrono>       // std::chrono_literals
#include <complex>      // std::complex/complex_literals
#include <iostream>     // std::cout
#include <string>       // std::string_literals
#include <string_view>  // std::string_view_literals
#include <thread>       // std::this_thread::sleep_for

using namespace std;

int main()
{
    cout << "i * i = " << 1i * 1i << '\n';
    cout << "Waiting for 500ms\n";
    this_thread::sleep_for(500ms);
    cout << "Hello world"s.substr(0, 5) << '\n';
    cout << "Hello world"sv.substr(6) << '\n';
}
