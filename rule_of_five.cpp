#include <vector>
#include <iostream>

struct S{
    S() { std::cout << "ctor" << std::endl;}
    ~S() { std::cout << "dtor" << std::endl;}
    S(const S&) { std::cout << "copy ctor" << std::endl;}
    S(S&&) noexcept  { std::cout << "move ctor" << std::endl;}
    S& operator= (const S&) { std::cout << "move ctor" << std::endl; return *this;}
    S& operator= (S&&) noexcept { std::cout << "move ctor" << std::endl; return *this;}
};

class A{
public: 
    A(S s) {}
};

class B:A{
public: 
    B(S s):A(std::move(s)) {}
};


int main() {
    S s;
    B b(std::move(s));
    return 0;
}
