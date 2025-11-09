#include <vector>
#include <iostream>
#include <algorithm>
#include <ctime>

template <class T>
void forEle(std::vector<T>& vTarget)
{
    std::for_each(vTarget.begin(), vTarget.end(), [](int val) { std::cout << val << " "; });
    std::cout << std::endl;
}

void test01()
{
    std::cout << __func__ << std::endl;
    std::vector<int> v1;
    std::vector<int> v2; 
    std::vector<int> vTarget; 
    for(int i = 0; i < 10; i++)
    {
        v1.push_back(i);
        v2.push_back(i + 100);

    }
    int size = v1.size() + v2.size();
    vTarget.resize(size);  // 目标容器必须要有 足够的容量
    std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), vTarget.begin());
    forEle(vTarget);
}

// std::sort 排序
class MyCompareSort
{
public:
    bool operator()(int v1, int v2)
    {
        return v1 > v2;
    }
};
void test02()
{
    std::cout << __func__ << std::endl;
    std::vector<int> v;
    v.push_back(30);
    v.push_back(3);
    v.push_back(10);
    v.push_back(12);
    v.push_back(60);

    std::sort(v.begin(), v.end(), MyCompareSort());
    forEle(v);

}


// std::randome_shuffle 洗牌，对元素的次序随机调整
void test03()
{
    srand(time(NULL));
    std::cout << __func__ << std::endl;
    std::vector<int> v;
    for(int i = 0; i < 10; i++)
        v.push_back(i);

    // 洗牌
    std::random_shuffle(v.begin(), v.end()); // 需要设置一个时间种子
    std::cout << v.size();
    forEle(v);
}


// std::reverse 反转
void test04()
{
    std::vector<int> v;
    for(int i = 0; i < 10; i++)
        v.push_back(i);

    std::cout << "反转前：" << std::endl;
    forEle(v);
    std::reverse(v.begin(), v.end());

    std::cout << "反转后：" << std::endl;
    forEle(v);
}

int main(void)
{
    test01();  // std::merge
    std::cout << std::endl;
    test02();  // std::sort
    std::cout << std::endl;
    test03();  // std::random_shuffle
    std::cout << std::endl;
    test04();  // std::reverse

    return 0;
}

/*

test01
0 1 2 3 4 5 6 7 8 9 100 101 102 103 104 105 106 107 108 109

test02
60 30 12 10 3

test03
3 8 7 4 1 6 2 9 0 5

反转前：
0 1 2 3 4 5 6 7 8 9
反转后：
9 8 7 6 5 4 3 2 1 0

*/