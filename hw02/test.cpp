#include <iostream>
#include <algorithm>
#include <memory>


class A
{
public:
    A(int a_) { this->a = a_; }
    void show() { std::cout << a << '\n'; }
private:
    int a;
};

int main()
{
    std::shared_ptr<A> aa = std::make_shared<A>(10);
    aa->show();
    std::shared_ptr<A> bb = aa;
    bb->show();
}