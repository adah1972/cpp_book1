#include <iostream>  // std::cout
#include <thread>    // std::thread

using namespace std;

class Obj1 {  // NOLINT(cppcoreguidelines-special-member-functions)
public:
    Obj1() { cout << "Obj1 is created\n"; }
    ~Obj1() { cout << "Obj1 is destroyed\n"; }
    void op() {}
};

class Obj2 {  // NOLINT(cppcoreguidelines-special-member-functions)
public:
    ~Obj2() { cout << "Obj2 is destroyed\n"; }
    void op() {}
};

thread_local Obj1 obj1;
thread_local Obj2 obj2;

int main()
{
    cout << "In main\n";
    std::thread{[] {
        cout << "In thread 1\n";
        obj1.op();
        cout << "Exiting thread 1\n";
    }}.join();
    std::thread{[] {
        cout << "In thread 2\n";
        obj2.op();
        obj1.op();
        cout << "Exiting thread 2\n";
    }}.join();
    cout << "Exiting main\n";
}
