#include <algorithm>  // std::max/min/minmax
#include <cassert>    // assert

using namespace std;

int main()
{
    int n = 1;
    int m = -1;
    assert(&min(n, m) == &m);
    assert(&max(n, m) == &n);
    assert(&(minmax(n, m).first) == &m);
    assert(&(minmax(n, m).second) == &n);

    assert(min({n, m, 5}) == m);
    // Can't compile: assert(&max({n, m}) == &n);
}
