#include <iostream>  // std::cout

using namespace std;

class length {
public:
    enum unit {
        metre,
        kilometre,
        millimetre,
        centimetre,
        inch,
        foot,
        yard,
        mile,
    };
    explicit length(double v, unit u = metre)
        : value_(v * factors[u])
    {
    }

    double value() const { return value_; };

private:
    double value_;

    static constexpr double factors[] = {
        1.0, 1000.0, 1e-3, 1e-2, 0.0254, 0.3048, 0.9144, 1609.344};
};

length operator+(length lhs, length rhs)
{
    return length(lhs.value() + rhs.value());
}

length operator""_m(long double v)
{
    return length(static_cast<double>(v), length::metre);
}

length operator""_cm(long double v)
{
    return length(static_cast<double>(v), length::centimetre);
}

int main()
{
    auto result = 1.0_m + 10.0_cm;
    cout << "Result is " << result.value() << "m\n";
}
