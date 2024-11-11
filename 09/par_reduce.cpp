#include <chrono>     // std::chrono::steady_clock
#include <execution>  // std::execution::par
#include <iostream>   // std::cout
#include <numeric>    // std::accumulate/reduce
#include <vector>     // std::vector

using namespace std;

int main()
{
    vector<double> v(10000000, 0.0625);

    {
        auto t1 = chrono::steady_clock::now();
        double result = accumulate(v.begin(), v.end(), 0.0);
        auto t2 = chrono::steady_clock::now();
        cout << "accumulate:   result " << result << " took "
             << (t2 - t1) / 1.0ms << " ms\n";
    }

    {
        auto t1 = chrono::steady_clock::now();
        double result = reduce(execution::seq, v.begin(), v.end());
        auto t2 = chrono::steady_clock::now();
        cout << "reduce (seq): result " << result << " took "
             << (t2 - t1) / 1.0ms << " ms\n";
    }

    {
        auto t1 = chrono::steady_clock::now();
        double result = reduce(execution::par, v.begin(), v.end());
        auto t2 = chrono::steady_clock::now();
        cout << "reduce (par): result " << result << " took "
             << (t2 - t1) / 1.0ms << " ms\n";
    }
}
