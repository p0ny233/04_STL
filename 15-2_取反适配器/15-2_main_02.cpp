/*
    不修改 GreaterThan5中的 operator函数逻辑，找到 小于5 的元素
        使用 取反适配器

    1. std::not1(函数对象)
    2. 继承 public std::unary_function<int, bool>
    3. 使得重载的operator()(int) 函数声明为 常函数
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

void test02()
{
    std::vector<int> v;
    for(int i = 0; i < 10; i++)
    {
        v.push_back(i);
    }

    // 找到小于5 的元素
    std::vector<int>::iterator ret = find_if(v.begin(), v.end(),  std::not1(GreaterThan5()));
    if(ret != v.end())
    {
        std::cout << "找到元素: " << *ret << std::endl;
    }
    else
    {
        std::cout << "未找到元素" << std::endl;
    }
}

int main2(void)
{
    test02();
    return 0;
}

// 找到元素: 0