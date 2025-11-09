/*
    找到 大于5 的元素
*/
#include <iostream>
#include <vector>

class GreaterThan5
{
public:
    bool operator()(int val)
    {
        return val > 5;
    }
};

void test01()
{
    std::vector<int> v;
    for(int i = 0; i < 10; i++)
    {
        v.push_back(i);
    }

    // 找到大于5 的元素
    std::vector<int>::iterator ret = find_if(v.begin(), v.end(), GreaterThan5());
    if(ret != v.end())
    {
        std::cout << "找到元素: " << *ret << std::endl;
    }
    else
    {
        std::cout << "未找到元素" << std::endl;
    }
}

int main1(void)
{
    test01();
    return 0;
}

// 找到元素: 6