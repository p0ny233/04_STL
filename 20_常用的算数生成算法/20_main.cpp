#include <vector>
#include <iostream>
#include <numeric>
#include <algorithm>

// std::accumulate
void test01()
{
    std::cout << __func__ << std::endl;
    std::vector<int> v;

    for(int i = 0; i <= 100; i++)
    {
        v.push_back(i);
    }
    int sum = std::accumulate(v.begin(), v.end(), 0);  
    // 第三个参数是 容器累加完成后，结果再加第三个参数值

    std::cout << "sum: " << sum << std::endl;

    sum = std::accumulate(v.begin(), v.end(), 1);  
    // 第三个参数是 容器累加完成后，结果再加第三个参数值

    std::cout << "sum: " << sum << std::endl;
}

// std::fill
void test02()
{
    std::cout << __func__ << std::endl;
    std::vector<int> v;
    v.resize(20);
    std::fill(v.begin(), v.end(), 33);
    std::for_each(v.begin(), v.end(), [](int val){std::cout << val << " ";});
}

int main(void)
{
    test01();
    std::cout << std::endl;
    test02();
    return 0;
}
/*

test01
sum: 5050
sum: 5051

test02
33 33 33 33 33 33 33 33 33 33 33 33 33 33 33 33 33 33 33 33

*/