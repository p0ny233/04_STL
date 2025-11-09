/*
    在MyPrint2 函数对象中的 operator() 再 添加1个参数
    如果给 函数对象中的 operator() 定义两个参数，那么就会报错，可以看 for_each的实现，
    内部在使用 函数对象时，只传递一个参数
        _Func(*_UFirst);
    因此，怎么将 operator 定义的两个参数变为一个参数???

    1. 使用 bind2nd(MyPrint, number); 进行绑定  // bind2nd 属于内建函数对象, 引入 functional
    2. MyPrint函数对象继承 binary_function<参数1类型, 参数2类型, 返回值类型>
        binary_function 是二元绑定，MyPrint的operator接收2个参数，因此是二元的
    3. MyPrint类的operator要加const变为常函数
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

class MyPrint2 : public std::binary_function<int, int ,void>
{
public:
    void operator()(int val, int base)const
    {
        std::cout << val + base << std::endl;
    }
};

void test2()
{
    std::vector<int> v;
    v.push_back(9);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    int n;
    std::cout << "输入 n的值："<< std::endl;
    std::cin >> n;

    for_each(v.begin(), v.end(), bind2nd(MyPrint2(), n));
}


int main(void)
{
    test2();
    return 0;
}

/*

输入 n的值：
1000
1009
1003
1004
1005

*/