#include <iostream>
#include <vector>
#include <algorithm>

// std::set_intersection 求两个容器的交集
// 两个容器必须是 有序序列
void test01()
{
    std::cout << __func__ << std::endl;
    std::vector<int> v1;    
    std::vector<int> v2;    
    for(int i = 0; i < 10; i++)
    {
        v1.push_back(i);
        v2.push_back(i + 5);
    }

    std::vector<int> vTarget;
    //int size = v1.size() > v2.size() ? v2.size() : v1.size();  // 因为是交集，所以取最小的size
    vTarget.resize(std::min(v1.size(), v2.size()));

    std::vector<int>::iterator itEnd = std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), vTarget.begin());
    // 一定要收返回值，才知道最后一个元素在哪里，否则会输出其余的元素(默认 0值)
    std::cout << "v1 与 v2 的交集: " << std::endl;

    std::for_each(vTarget.begin(), itEnd, [](int val) {std::cout << val << " ";});
    std::cout << std::endl;
}

// std::set_union 求两个容器的并集
// 两个容器必须是 有序序列
void test02()
{
    std::cout << __func__ << std::endl;
    std::vector<int> v1;
    std::vector<int> v2;
    for(int i = 0; i < 10; i++)
    {
        v1.push_back(i);
        v2.push_back(i + 5);
    }
    std::vector<int> vTarget;
    vTarget.resize(v1.size() + v2.size());  // 并集，最大容量
    std::vector<int>::iterator itEnd = std::set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), vTarget.begin());
    std::cout << "v1 与 v2 的并集: " << std::endl;
    std::for_each(vTarget.begin(), itEnd, [](int val) {std::cout << val << " "; });
    std::cout << std::endl;
}

// std::set_difference 求两个容器的差集
// 两个容器必须是 有序序列
void test03()
{
    std::cout << __func__ << std::endl;
    std::vector<int> v1;
    std::vector<int> v2;
    for(int i = 0; i < 10; i++)
    {
        v1.push_back(i);
        v2.push_back(i + 5);
    }
    std::vector<int> vTarget;

    vTarget.resize(std::max(v1.size(), v2.size()));  // 差集，取最大容量

    // v1 与 v2 的差集
    std::cout << "v1 与 v2 的差集: " << std::endl;
    std::vector<int>::iterator itEnd = std::set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), vTarget.begin());
    std::for_each(vTarget.begin(), itEnd, [](int val) {std::cout << val << " "; });
    std::cout << std::endl;

    // v2 与 v1 的差集
    std::cout << "v2 与 v1 的差集: " << std::endl;
    itEnd = std::set_difference(v2.begin(), v2.end(), v1.begin(), v1.end(), vTarget.begin());
    std::for_each(vTarget.begin(), itEnd, [](int val) {std::cout << val << " "; });
    std::cout << std::endl;
}

int main(void)
{
    test01();
    std::cout << std::endl;
    test02();
    std::cout << std::endl;
    test03();
    std::cout << std::endl;
    return 0;
}

/*

test01
v1 与 v2 的交集:
5 6 7 8 9

test02
v1 与 v2 的并集:
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14

test03
v1 与 v2 的差集:
0 1 2 3 4
v2 与 v1 的差集:
10 11 12 13 14

*/