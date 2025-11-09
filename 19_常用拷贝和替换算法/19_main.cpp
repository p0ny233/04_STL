#include<vector>
#include <iostream>
#include <algorithm>
#include <iterator>  // 访问 ostream_iterator
#include <functional>

template <class T>
void forEle(std::vector<T>& v)
{
    std::for_each(v.begin(), v.end(), [](T& val){ std::cout << val << " "; });
}

// std::copy算法，将容器内指定范围的元素拷贝到另一个容器中
void test01()
{
    std::cout << __func__ << std::endl;
    std::vector<int> v1;
    std::vector<int> v2;
    for (int i = 0; i < 10; i++)
        v1.push_back(i);

    // 同样的，目标容器也需要有足够的容量
    v2.resize(v1.size());
    std::copy(v1.begin(), v1.end(), v2.begin());
    forEle(v2);
}

// std::copy 的其它用法，拷贝到输出流
void test02()
{
    std::cout << __func__ << std::endl;
    std::vector<int> v1;
    for(int i = 0; i < 10; i++)
        v1.push_back(i);
    std::copy(v1.begin(), v1.end(), std::ostream_iterator<int>(std::cout, " "));
}

// std::replace，将值为3替换为 3000
void test03()
{
    std::cout << __func__ << std::endl;
    std::vector<int> v1;
    for(int i = 0; i < 10; i++)
        v1.push_back(i);
    std::replace(v1.begin(), v1.end(), 3, 3000);
    forEle(v1);
}

// std::replace_if，将所有大于3的数全部替换为 666
class Greathan3 : public std::binary_function<int, int, bool>
{
public:
    bool operator()(int v1, int v2)const
    {
        return v1 > v2;
    }
};
void test04()
{
    std::cout << __func__ << std::endl;
    std::vector<int> v1;
    for(int i = 0; i < 10; i++)
        v1.push_back(i);

    int num = 3;
    std::replace_if(v1.begin(), v1.end(), std::bind2nd(Greathan3(), num), 666);
    forEle(v1);
}

// std::swap 交换
void test05()
{
    std::cout << __func__ << std::endl;
    std::vector<int> v1;
    for(int i = 0; i < 10; i++)
        v1.push_back(i);

    std::vector<int> v2(10, 22);  // 10个22
    std::cout << "交换前如下：" << std::endl;
    forEle(v1);
    std::cout << std::endl;
    forEle(v2);
    std::swap(v1, v2);
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "交换后如下：" << std::endl;
    forEle(v1);
    std::cout << std::endl;
    forEle(v2);
}

int main(void)
{
    test01();
    std::cout << std::endl;
    std::cout << std::endl;
    test02();
    std::cout << std::endl;
    std::cout << std::endl;
    test03();
    std::cout << std::endl;
    std::cout << std::endl;
    test04();
    std::cout << std::endl;
    std::cout << std::endl;
    test05();
    return 0;
}
/*

test01
0 1 2 3 4 5 6 7 8 9

test02
0 1 2 3 4 5 6 7 8 9

test03
0 1 2 3000 4 5 6 7 8 9

test04
0 1 2 3 666 666 666 666 666 666

test05
交换前如下：
0 1 2 3 4 5 6 7 8 9
22 22 22 22 22 22 22 22 22 22

交换后如下：
22 22 22 22 22 22 22 22 22 22
0 1 2 3 4 5 6 7 8 9

*/