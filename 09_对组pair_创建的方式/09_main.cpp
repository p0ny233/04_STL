#include <iostream>

class Person
{

};
// 第一种创建 对组的方式
void test01()
{
    std::pair<std::string, int> p1("Tom", 11);
    std::cout << "p1.first: " << p1.first << std::endl;
    std::cout << "p1.second: " << p1.second << std::endl;
}

// 第二种创建 对组的方式 (推荐)
void test02()
{
    std::pair<std::string, int> p2 = std::make_pair("jack", 12);
    std::cout << "p2.first: " << p2.first << std::endl;
    std::cout << "p2.second: " << p2.second << std::endl;
}

void test03()
{
    std::make_pair<int, int>(1, 123);
}
int main(void)
{
    test01();
    std::cout << std::endl;
    test02();
    return 0;
}
/*

p1.first: Tom
p1.second: 11

p2.first: jack
p2.second: 12

*/