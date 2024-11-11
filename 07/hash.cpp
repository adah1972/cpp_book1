#include <functional>  // std::hash
#include <iostream>    // std::cout
#include <string>      // std::string

using namespace std;

int main()
{
    cout << hex;

    auto hp = hash<int*>();
    cout << "hash(nullptr)  = " << hp(nullptr) << '\n';

    auto hs = hash<string>();
    cout << "hash(\"world\")  = " << hs(string("world")) << '\n';
    cout << "hash(\"world \") = " << hs(string("world ")) << '\n';
}
