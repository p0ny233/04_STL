#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

// 取反 negate<int>
void test01()
{
    std::negate<int> n;
    std::cout << n(11) << std::endl;
}

// 加法 `plus<int>`
void test02()
{
    std::plus<int> p;
    std::cout << p(1, 2) << std::endl;
}

// 大于 `greater<int>`
void test03()
{
    std::vector<int> v;
    v.push_back(30);
    v.push_back(10);
    v.push_back(40);
    v.push_back(80);

    for_each(v.begin(), v.end(), [](int val){std::cout << val << " ";});
    std::cout << std::endl;

    // 指定从大到小排序
    std::cout << "排序后：" << std::endl;
    sort(v.begin(), v.end(), std::greater<int>());

    for_each(v.begin(), v.end(), [](int val) {std::cout << val << " "; });
    std::cout << std::endl;
}

int main(void)
{
    test01();
    test02();
    test03();
    return 0;
}

/*

-11
3
30 10 40 80
排序后：
80 40 30 10

*/
