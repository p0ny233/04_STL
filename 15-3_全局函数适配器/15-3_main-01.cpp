/*
    以下代码仅仅是遍历元素输出，若要在 myPrint中 实现让用户自定义基于某个数相加，并计算得出结果，怎么实现？
        看 15-3_main-02.cpp

*/
#include <vector>
#include <iostream>
#include <algorithm>

void myPrint(int val)
{
    std::cout << val << std::endl;
}

void test01()
{
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    
    for_each(v.begin(), v.end(), myPrint);
}

int main1(void)
{
    test01();
    return 0;
}
/*
1
2
3
4
5

*/