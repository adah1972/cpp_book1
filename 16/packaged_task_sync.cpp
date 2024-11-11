#include <chrono>    // std::chrono_literals
#include <future>    // std::packaged_task
#include <iostream>  // std::cout
#include <thread>    // std::this_thread::sleep_for

using namespace std;

int work()
{
    this_thread::sleep_for(2s);
    return 42;
}

int main()
{
    packaged_task<int()> task{work};

    this_thread::sleep_for(1s);
    cout << "Calculating synchronously\n";
    task();
    cout << "Answer: " << task.get_future().get() << '\n';
    task.reset();
    task();
    cout << "Answer: " << task.get_future().get() << '\n';
}
