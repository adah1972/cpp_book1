#include <chrono>    // std::chrono::*
#include <format>    // std::cout
#include <iostream>  // std::format

using namespace std;

int main()
{
    auto now = chrono::system_clock::now();
    cout << "UTC time:   " << now << '\n';
    auto trunc_now = chrono::time_point_cast<chrono::seconds>(now);
    cout << "UTC time:   " << trunc_now << '\n';
    auto local_tz = chrono::get_tzdb().current_zone();
    auto zoned_now = chrono::zoned_time(local_tz, trunc_now);
    cout << format("Local time: {:%F %T}", zoned_now) << '\n';
    cout << format("Local time: {:%F %H:%M:%S %Z}", zoned_now)
         << '\n';

    cout << "Last days of months in 2024:\n";
    constexpr auto one_month = chrono::months{1};
    using std::chrono::last;
    for (auto ymd = 2024y/1/last; ymd < 2025y/1/1; ymd += one_month) {
        cout << ' ' << chrono::sys_days{ymd} << '\n';
    }
}
