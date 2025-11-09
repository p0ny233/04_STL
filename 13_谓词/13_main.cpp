#include <iostream>
#include <vector>
#include <algorithm>

// 一元谓词
class GreatThan20  // 找比20大的
{
public:
    // 返回值为bool
    bool operator()(int val)
    {
        return val > 20;
    }
};

void test01()
{
    std::vector<int> V;
    V.push_back(10);
    V.push_back(20);
    V.push_back(30);
    V.push_back(40);
    V.push_back(50);

    std::vector<int>::iterator ret = find_if(V.begin(), V.end(), GreatThan20());
    if (ret != V.end())
        std::cout << "找到比20大的数: " << *ret << std::endl;
    else
        std::cout << "未找到" << std::endl;

}

// 一元仿函数
class MyPrint
{
public:
    void operator()(int val)
    {
        std::cout << val << " ";
    }
};



// 二元谓词
class MyCompareInt
{
public:
    bool operator()(int v1, int v2)
    {
        return v1 > v2;
    }
};

void test02()
{
    std::vector<int> V;
    V.push_back(10);
    V.push_back(30);
    V.push_back(20);
    V.push_back(50);
    V.push_back(40);

    // 使用 for_each 搭配 一元仿函数 输出每个元素
    for_each(V.begin(), V.end(), MyPrint());
    std::cout << std::endl;

    // 使用 sort和二元谓词 对 vector中的元素从大到小排序 
    sort(V.begin(), V.end(), MyCompareInt());

    // 使用 for_each 搭配 lambda表达式 遍历输出每个元素
    for_each(V.begin(), V.end(), [](int val){std::cout << val << " "; });
    std::cout << std::endl;
    
}

int main(void)
{
    test01();   
    std::cout << std::endl;
    test02();   
    return 0;
}
/*

找到比20大的数: 30

10 30 20 50 40
50 40 30 20 10

*/