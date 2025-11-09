/*

应用场景：

当需要向序列两端频繁的添加或删除元素时，应首选 deque 容器。

特点
- 双端队列容器，内存是分段连续的，类似于一个动态的二维数组，如下图
- 不能保证所有元素的内存都是连续的
- 适合`头插/删` / `尾插/删`，时间复杂度`O(1)`

*/
#include <iostream>
#include <deque>

void printDeque(std::deque<int> &d)
{
    // iterator         普通迭代器
    // reverse_iterator 反转迭代器
    // const_iterator   只读迭代器
    for(std::deque<int>::const_iterator it = d.begin(); it != d.end(); it++)
    {

        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void  test01()
{
    std::deque<int> deq;
    deq.push_back(10);
    deq.push_back(20);
    deq.push_back(30);
    deq.push_back(40);
    deq.push_back(50);

    std::deque<int> d2;
    d2 = deq;
    printDeque(d2);

    if(d2.empty())
    {
        std::cout << "d2 为空" << std::endl;
    }
    else 
    {
        std::cout << "d2 不为空" << std::endl;
    }
}

// 尾插、尾删 / 头插、头删
void test02()
{
    std::cout << __func__ << std::endl;
    std::deque<int> deq;
    deq.push_back(1);
    deq.push_back(2);
    deq.push_back(3);
    deq.push_back(4);
    deq.push_front(300);
    deq.push_front(100);
    deq.push_front(200);
    printDeque(deq);

    deq.pop_back();   // 尾删
    deq.pop_front();  // 头删

    printDeque(deq);

    // 获取第一个元素 / 最后一个元素
    std::cout << "front: " << deq.front() << std::endl;
    std::cout << "back: " << deq.back() << std::endl;
}

// 插入insert / 删除 erase / 清空
void test03()
{
    std::cout << __func__ << std::endl;
    std::deque<int> deq;
    deq.push_back(2);
    deq.push_back(4);
    deq.push_back(5);
    std::deque<int>::iterator it = deq.begin();
    deq.insert(++it, 3);  // 插入元素
    printDeque(deq);

    it = deq.begin();  // 迭代器失效了，需要重新获取迭代器
    deq.insert(it, 5, 1);
    printDeque(deq);

    deq.erase(deq.begin() + 3);  // 仅提供一个元素的迭代器
    printDeque(deq);

    deq.erase(deq.begin(), deq.end());  // 清空元素   等价于 deq.clear()
    printDeque(deq);
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

10 20 30 40 50
d2 不为空

test02
200 100 300 1 2 3 4
100 300 1 2 3
front: 100
back: 3

test03
2 3 4 5
1 1 1 1 1 2 3 4 5
1 1 1 1 2 3 4 5

*/