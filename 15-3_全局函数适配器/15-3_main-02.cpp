/*
    1. 使用 std::ptr_fun() 将 函数指针包装成函数对象
    2. 由于 for_each 每次调用，都是只将当前元素作为参数传递，因此需要binder2nd和 ptr_fun介入，给普通函数做适配功能
*/
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

void myPrint(int val, int base)
{
    std::cout << val + base << std::endl;
}

void test02()
{
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);

    for_each(v.begin(), v.end(), std::bind2nd(std::ptr_fun(myPrint), 1000));
    // bind2nd对象的 op属性绑定 pointer_to_unary_function 对象
    // bind2nd对象的 value属性绑定 值1000
    // 调用 bind2nd对象(left) 相当于 op(left, value) 等价于 op(容器的元素,1000)
    // pointer_to_unary_function对象(容器的元素,1000)，其中pointer_to_unary_function对象的 _Pfun属性绑定myPrint
    // _Pfun(left, right) 等价于 _Pfun(容器的元素, 1000)
}

int main(void)
{
    test02();
    return 0;
}
/*

1001
1002
1003
1004
1005

*/