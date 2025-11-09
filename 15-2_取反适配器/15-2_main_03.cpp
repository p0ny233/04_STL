/*
    更复杂的的写法，对 15-2_main_02.cpp 升级。
        15-2_main_02.cpp 对找到小于5的元素中的 5 是写死 了，那么怎么做才能由用户自行指定呢？？？

    1. 

*/
#include <iostream>
#include <vector>
#include <functional>

class GreaterThan5 : public std::unary_function<int, bool>
{
public:
    bool operator()(int val) const
    {
        return val > 5;
    }
};

void test03()
{
    std::vector<int> v;
    for(int i = 0; i < 10; i++)
    {
        v.push_back(i);
    }
    int n;
    std::cout << "请输入 n的值：";
    std::cin >> n;

    // 按顺序遍历容器，找到第一个 小于等于 n 的元素
    std::vector<int>::iterator ret = find_if(v.begin(), v.end(), std::not1(std::bind2nd(std::greater<int>(), n)));
    // 对 33行代码的剖析 https://tcnckk4dyn0w.feishu.cn/wiki/MblPwjQnviI0UDk3K7Ncmct8n8b#MABXdaHxfoq86vxM5AgcJJPdn3d
    
    if(ret != v.end())
    {
        std::cout << "找到元素: " << *ret << std::endl;
    }
    else
    {
        std::cout << "未找到元素" << std::endl;
    }
}

int main(void)
{
    test03();
    return 0;
}

/*

请输入 n的值：5
找到元素: 0

*/