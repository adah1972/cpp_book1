#include <iostream>  // std::cout
#include <utility>   // std::move

using namespace std;

bool cond = false;

class A {
public:
    A(int num = 0) : num_{num}
    {
        cout << "Create A(" << num_ << ")\n";
    }
    ~A()
    {
        cout << "Destroy A(" << num_ << ")\n";
    }
    A(const A& rhs) : num_{rhs.num_}
    {
        cout << "Copy A(" << rhs.num_ << ")\n";
    }
    A& operator=(const A& rhs)
    {
        cout << "Copy= A(" << rhs.num_ << ") <- " << num_ << "\n";
        num_ = rhs.num_;
        return *this;
    }
#ifndef DISABLE_MOVE
    A(A&& rhs) noexcept : num_(rhs.num_)
    {
        cout << "Move A(" << rhs.num_ << ")\n";
        rhs.num_ = -1;
    }
    A& operator=(A&& rhs) noexcept
    {
        cout << "Move= A(" << rhs.num_ << ") <- " << num_ << "\n";
        num_ = rhs.num_;
        rhs.num_ = -1;
        return *this;
    }
#endif

private:
    int num_;
};

A getA_unnamed_rvo()
{
    return A();
}

A getA_named_rvo()
{
    A a;
    return a;
}

A getA_named_rvo_suppressed()
{
    A a;
    return std::move(a);
}

A getA_no_rvo1()
{
    A a(1);
    if (cond) {
        return A();
    } else {
        return a;
    }
}

A getA_no_rvo2()
{
    A a1(1);
    A a2(2);
    if (cond) {
        return a1;
    } else {
        return a2;
    }
}

int main()
{
    {
        cout << "*** Calling getA_unnamed_rvo\n";
        A a = getA_unnamed_rvo();
    }
    {
        cout << "*** Calling getA_named_rvo\n";
        A a = getA_named_rvo();
    }
    {
        cout << "*** Calling getA_named_rvo_suppressed\n";
        A a = getA_named_rvo_suppressed();
    }
    {
        cout << "*** Calling getA_no_rvo1\n";
        A a = getA_no_rvo1();
    }
    {
        cout << "*** Calling getA_no_rvo2\n";
        A a = getA_no_rvo2();
    }
}
