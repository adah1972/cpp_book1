#include <stdio.h>  // puts

class Shape {
public:
    virtual ~Shape() {}
};

class Circle : public Shape {
public:
    Circle() { puts("Circle()"); }
    ~Circle() { puts("~Circle()"); }
};

class Triangle : public Shape {
public:
    Triangle() { puts("Triangle()"); }
    ~Triangle() { puts("~Triangle()"); }
};

class Result {
public:
    Result() { puts("Result()"); }
    ~Result() { puts("~Result()"); }
};

Result process_shape(const Shape& shape1, const Shape& shape2)
{
    puts("process_shape()");
    return Result();
}

int main()
{
    puts("main()");
    process_shape(Circle(), Triangle());
    puts("something else");
}
