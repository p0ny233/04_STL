/*
- 逻辑结构是队列
- 物理结构可以是数组或链表
- 主要用于多线程之间的数据共享。
- 先进先出
*/
#include <iostream>
#include <queue>

class Person
{
    friend std::ostream& operator<<(std::ostream& out, Person& ref);
public:
    std::string mName;
    Person(std::string name)
    {
        mName = name;
        std::cout << this->mName << " Person 构造函数" << std::endl;
    }
    Person(const Person& ref)
    {
        mName = ref.mName;
        std::cout << this->mName << " Person 拷贝构造函数" << std::endl;
    }
    ~Person()
    {
        std::cout << this->mName << " Person 析构函数" << std::endl;
    }
};

std::ostream& operator<<(std::ostream& out, Person& ref)
{
    out << ref.mName << std::endl;
    return out;    
}


void test01()
{
    Person p1("p1");
    Person p2("p2");
    Person p3("p3");
    Person p4("p4");

    std::queue<Person> q;
    // 入队
    q.push(p1);
    q.push(p2);
    q.push(p3);
    q.push(p4);
    std::cout << "队尾元素: " << q.back() << " " << std::endl;  // 返回队尾的元素

    while(!q.empty())
    {
        std::cout << "队头元素: " << q.front() << " " << std::endl;  // 返回队头的元素
        q.pop();  // 删除队头的元素
    }

}

int main(void)
{
    test01();
    return 0;
}

/*

p1 Person 构造函数
p2 Person 构造函数
p3 Person 构造函数
p4 Person 构造函数
p1 Person 拷贝构造函数
p2 Person 拷贝构造函数
p3 Person 拷贝构造函数
p4 Person 拷贝构造函数
队尾元素: p4

队头元素: p1

p1 Person 析构函数
队头元素: p2

p2 Person 析构函数
队头元素: p3

p3 Person 析构函数
队头元素: p4

p4 Person 析构函数
p4 Person 析构函数
p3 Person 析构函数
p2 Person 析构函数
p1 Person 析构函数

*/