#include <iostream>
#include <vector>

void printVector(std::vector<int>& ref)
{
    for(std::vector<int>::iterator it = ref.begin(); it < ref.end(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

// 1. 构造
void test01()
{
    std::cout << __func__ << std::endl;
    // 默认构造
    std::vector<int> v1;
    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(30);
    v1.push_back(40);
    v1.push_back(50);

    printVector(v1);

    // 有参构造，将 v1容器的 v1.begin()到 v1.end() 区间的元素拷贝一份到 v2
    std::vector<int> v2(v1.begin(), v1.end());
    printVector(v2);
}

// 2. 赋值
void test02()
{
    std::cout << __func__ << std::endl;

    std::vector<int> v1;
    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(30);
    v1.push_back(40);
    v1.push_back(50);

    printVector(v1);
    
    std::vector<int> v3;
    v3.assign(v1.begin(), v1.end());
    printVector(v3);

    std::vector<int> v4(5, 100);  // 5 个100
    printVector(v4);

    // 互换
    v3.swap(v4);
    std::cout << "\nv3和v4 互换后：" << std::endl;
    printVector(v3);
    printVector(v4);
}

// 3. vector大小操作、是否为空 empty、重置大小 resize、front 、back 
void test03()
{
    std::cout << __func__ << std::endl;

    std::vector<int> v1;
    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(30);
    v1.push_back(40);
    v1.push_back(50);

    if(v1.empty())
    {
        std::cout << "v1 为空";
    }
    else
    {
        std::cout << "v1 不为空，大小为：" << v1.size() << std::endl;
    }

    v1.resize(10);    // 超出 5 个，超出的部分 默认值为 0
    printVector(v1);  // 10 20 30 40 50 0 0 0 0 0

    v1.resize(20, 66);   // 超出 10 个，超出的部分 默认值为 66
    printVector(v1);  // 10 20 30 40 50 0 0 0 0 0 66 66 66 66 66 66 66 66 66 66

    v1.resize(3);     // 多余的部分全部删除
    printVector(v1);  // 10 20 30


    std::cout << "front: " << v1.front() << std::endl;
    std::cout << "back: " << v1.back() << std::endl;

}

// 4. vector插入和删除
void test04()
{
    std::cout << __func__ << std::endl;
    std::vector<int> v1;
    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(30);
    v1.push_back(40);
    v1.insert(v1.begin() + 1, 3, 666);  // 在 迭代器指向的位置  插入 3 个 666
    printVector(v1);  // 10 666 666 666 20 30 40
    
    v1.insert(v1.begin(), 99);  // 在首元素位置 插入  99
    printVector(v1);  // 99 10 666 666 666 20 30 40

    // 删除最后一个元素
    v1.pop_back();
    printVector(v1);  // 99 10 666 666 666 20 30

    // 删除首元素
    v1.erase(v1.begin());
    printVector(v1);  // 10 666 666 666 20 30

    // 删除容器中所有元素
    v1.erase(v1.begin(), v1.end());  // 等价于 v1.clear();
    printVector(v1);  // 

}

// 5. 巧用 swap收缩内存
void test05()
{
    std::cout << __func__ << std::endl;
    std::vector<int> v1;
    for(int i = 0; i < 10000; i++)
    {
        v1.push_back(i);
    }

    std::cout << "v1 的容量: " << v1.capacity() << std::endl;
    std::cout << "v1 的size: " << v1.size() << std::endl;
    
    // 使用匿名对象 交换
    // 1. 先resize
    v1.resize(3);
    std::cout << "resize 后 v1 的容量: " << v1.capacity() << std::endl;
    std::cout << "resize 后 v1 的size: " << v1.size() << std::endl;

    // 2. 使用v初始化匿名对象，交换后，匿名对象指向v1原始的内存，然后就释放掉
    std::vector<int>(v1).swap(v1);  
    // 实际上是利用了 vector的拷贝构造，在其内部拷贝传进来的实例的维护内存，那么会想到要开辟多大空间
    // 如果用size来开辟空间，刚好就合理利用了，不多不少。

    std::cout << "swap 后 v1 的容量: " << v1.capacity() << std::endl;
    std::cout << "swap 后 v1 的size: " << v1.size() << std::endl;
}

// 6. 巧用 reserve 预留空间
void test06()
{
    std::cout << __func__ << std::endl;
    std::vector<int> v1;
    int* p = NULL;
    int num = 0;
    for(int i = 0; i < 10000; i++)
    {
        v1.push_back(i);  // 要注意 vector的动态内存扩展。当容量不够，将会重新找内存空间，因此 要不停进入if语句块。
        if(p != &v1[0])
        {
            p = &v1[0];
            num++;  // 记录vector的动态数组的首地址的变化次数
        }
    }
    std::cout << "num: " << num << std::endl;  // num: 24
    // 说明 push_back 10000个数据，就要扩展 24次不同的内存(开辟新的内存，拷贝数据，释放原始的内存)

    // 使用预留空间，减少 找24次不同内存的操作
    std::vector<int> v2;
    v2.reserve(10000);
    int num2 = 0;
    for(int i = 0; i < 10000; i++)
    {
        v2.push_back(i);  // 要注意 vector的动态内存扩展。当容量不够，将会重新找内存空间，因此 要不停进入if语句块。
        if(p != &v2[0])
        {
            p = &v2[0];
            num2++;  // 记录vector的动态数组的首地址的变化次数
        }
    }
    std::cout << "num2: " << num2 << std::endl;  // num2: 1
    // 预留内存空间后，不需要再找 24次内存，只需要一次

}

// 7. 利用逆序迭代器 进行逆序遍历 vector
void test07()
{
    std::cout << __func__ << std::endl;
    std::vector<int> v1;
    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(30);
    v1.push_back(40);

    // reverse_iterator 逆序迭代器类型
    for(std::vector<int>::reverse_iterator reit = v1.rbegin(); reit != v1.rend(); reit++)
    {
        std::cout << *reit << " ";
    }
    std::cout << std::endl;
}

int main(void)
{
    // 1. 构造
    test01();
    std::cout << std::endl;
    // 2. 赋值
    test02();
    std::cout << std::endl;

    // 3. vector大小操作、是否为空 empty、重置大小 resize、front 、back 
    test03();
    std::cout << std::endl;

    // 4. vector插入和删除
    test04();
    std::cout << std::endl;

    // 5. 巧用 swap收缩内存
    test05();
    std::cout << std::endl;

    // 6. 巧用 reserve 预留空间
    test06();
    std::cout << std::endl;

    // 7. 利用逆序迭代器 进行逆序遍历 vector
    test07();
    std::cout << std::endl;
    return 0;
}

/*

test01
10 20 30 40 50
10 20 30 40 50

test02
10 20 30 40 50
10 20 30 40 50
100 100 100 100 100

v3和v4 互换后：
100 100 100 100 100
10 20 30 40 50

test03
v1 不为空，大小为：5
10 20 30 40 50 0 0 0 0 0
10 20 30 40 50 0 0 0 0 0 66 66 66 66 66 66 66 66 66 66
10 20 30
front: 10
back: 30

test04
10 666 666 666 20 30 40
99 10 666 666 666 20 30 40
99 10 666 666 666 20 30
10 666 666 666 20 30


test05
v1 的容量: 12138
v1 的size: 10000
resize 后 v1 的容量: 12138
resize 后 v1 的size: 3
swap 后 v1 的容量: 3
swap 后 v1 的size: 3

test06
num: 24
num2: 1

test07
40 30 20 10

*/