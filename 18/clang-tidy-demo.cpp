#include <stddef.h>  // NULL

struct St1 {
    int v1;
    int v2;
};

struct St2 {
    int v1{};
    int v2;
};

struct St3 {
    int v1{};
    int v2{};
};

class Shape {
public:
    virtual ~Shape() = default;
};

class ShapeWrapper {
public:
    explicit ShapeWrapper(Shape* ptr = NULL) : ptr_(ptr) {}
    ~ShapeWrapper() { delete ptr_; }
    Shape* get() const { return ptr_; }

private:
    Shape* ptr_;
};

int main()
{
    St1 st1;
    St2 st2;
    St3 BadName;
}
