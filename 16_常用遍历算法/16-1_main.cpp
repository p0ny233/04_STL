#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>

class MyPrint
{
public:
    int count = 0;
    void operator()(int val)
    {
        std::cout << val << " ";
        count++;
    }
};


// for_each 遍历算法
// 1. for_each 有返回值：返回 传入的第三个参数
void test01()
{
    std::cout << __func__ << std::endl;
    std::vector<int> v;
    v.push_back(1);
    v.push_back(3);
    v.push_back(4);
    v.push_back(2);

    MyPrint print = std::for_each(v.begin(), v.end(), MyPrint());
    std::cout << "\nprint.count: " << print.count << std::endl;

}

// 2. for_each 可以绑定参数 输出，适配器
class MyPrint2 : public std::binary_function<int, int, void> 
{
public:
    void operator()(int val, int base) const
    {
        std::cout << val + base << " ";
    }
};
void test02()
{
    std::cout << __func__ << std::endl;
    std::vector<int> v;
    v.push_back(1);
    v.push_back(3);
    v.push_back(4);
    v.push_back(2);

    std::for_each(v.begin(), v.end(), std::bind2nd(MyPrint2(), 1000));
    std::cout << std::endl;
    
}

// transform 遍历算法：从一个容器中搬运到另一个容器，
// 并在搬运的过程中可以执行对元素进行额外的操作

class MyTransform
{
public:
    int operator()(int val)
    {
        // 在搬运过程中对元素进行额外的操作
        return val+100;
    }
};

void test03()
{
    std::cout << __func__ << std::endl;
    std::vector<int> v1;
    v1.push_back(1);
    v1.push_back(3);
    v1.push_back(4);
    v1.push_back(2);
    
    std::vector<int> v2;

    v2.resize(v1.size());
    
    std::transform(v1.begin(), v1.end(), v2.begin(), MyTransform());    
    std::cout << "v2的元素: " << std::endl;
    std::for_each(v2.begin(), v2.end(), MyPrint());
    std::cout << std::endl;
}

int main(void)
{
    test01();
    std::cout << std::endl;
    test02();
    std::cout << std::endl;
    test03();
    return 0;
}
/*

test01
1 3 4 2
print.count: 4

test02
1001 1003 1004 1002

test03
v2的元素:
101 103 104 102

*/