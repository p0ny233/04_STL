/*
    基于15-1_main.cpp实现让用户指定基于某个数，进行计算输出结果，
    怎么做，看 15-2_main.cpp
*/
#include <iostream>
#include <vector>
#include <algorithm>

class MyPrint
{
public:
    void operator()(int val)
    {
        std::cout << val << std::endl;
    }
};

void test()
{
    std::vector<int> v;
    v.push_back(9);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    
    for_each(v.begin(), v.end(), MyPrint());
}


int main1(void)
{
    test();
    return 0;
}
/*

9
3
4
5

*/