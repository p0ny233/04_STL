#include <iostream>
class Person
{
public:
    template <class T>
    void test01();
};

template <class T>
void Person::test01()
{
    T a;
    std::cout << "hello" << std::endl;
}

int main(void)
{
    Person p1;
    p1.test01<int>();
    return 0;
}

// 可编译可正常运行