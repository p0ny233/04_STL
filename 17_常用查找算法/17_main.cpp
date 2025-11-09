#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

// std::find 查找基本数据类型
void test01()
{
    std::cout << __func__ << std::endl;
    std::vector<int> v;
    for(int i = 0; i < 10; i++)
    {
        v.push_back(i);
    }

    std::vector<int>::iterator ret = std::find(v.begin(), v.end(), 15);  // 返回迭代器类型
    if (ret != v.end())
        std::cout << "找到元素: " << *ret << std::endl;
    else
        std::cout << "未找到元素" << std::endl;
}


// std::find 查找自定义数据类型，vector内部存储 自定义数据类型的实体
class Person
{
public:
    std::string mName;
    int mAge;
    Person(std::string name, int age) : mName(name), mAge(age){}
    bool operator==(const Person& p)
    {
        if (this->mName == p.mName && this->mAge == p.mAge)
            return true;
        return false;
    }
};

void test02()
{
    std::cout << __func__ << std::endl;
    Person p1("aaa", 10);
    Person p2("bbb", 20);
    Person p3("ccc", 13);
    Person p4("ddd", 14);
    Person p5("eee", 12);

    std::vector<Person> v;
    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    v.push_back(p4);
    v.push_back(p5);

    std::vector<Person>::iterator ret = std::find(v.begin(), v.end(), p4);
    /*
        find 对于自定义的数据类型，要在内部重载 operator==() 运算符
            因为 find内部有一行 if (*_First == _Val)，if条件，条件就调用了 == 运算符，因此需要重载
                
    */
    if(ret != v.end())
        std::cout << "找到元素, 姓名：" << ret->mName << "，年龄：" << ret->mAge << std::endl;
    else
        std::cout << "未找到元素" << std::endl;
}

// std::find_if 查找自定义数据类型，vector内部存储 自定义数据类型的指针
class ComparePerson : public std::binary_function<const Person*, const Person*, bool>
{
public:
    bool operator()(const Person* p1,const Person* p2)const
    {
        return (p1->mName == p2->mName && p1->mAge == p2->mAge);
    }
};

void test03()
{
    std::cout << __func__ << std::endl;
    std::vector<Person*> v;
    Person p1("aaa", 10);
    Person p2("bbb", 20);
    Person p3("ccc", 13);
    Person p4("ddd", 14);
    Person p5("eee", 12);
    v.push_back(&p1);
    v.push_back(&p2);
    v.push_back(&p3);
    v.push_back(&p4);
    v.push_back(&p5);

    Person* condicate = new Person("bbb", 20);

    // 内部是直接比较内存地址，比较内存地址没有意义，换成条件查找 find_if，传入仿函数
    //std::vector<Person*>::iterator ret = find(v.begin(), v.end(), condicate);
    

    std::vector<Person*>::iterator ret = std::find_if(v.begin(), v.end(), std::bind2nd(ComparePerson(), condicate));
    if(ret != v.end())
    {
        std::cout << "匹配到了，姓名：" << (*ret)->mName << ", 年龄: " << (*ret)->mAge << std::endl;
    }
    else
    {
        std::cout << "未找到元素" << std::endl;

    }

}

// std::adjacent_find 查找相邻的重复的元素
void test04()
{
    std::cout << __func__ << std::endl;
    std::vector<int> v; 
    v.push_back(1);
    v.push_back(300);
    v.push_back(100);
    v.push_back(300);
    v.push_back(100);
    v.push_back(200);
    v.push_back(200);
    v.push_back(100);
    std::vector<int>::iterator ret = std::adjacent_find(v.begin(), v.end());
    if(ret != v.end())
    {
        std::cout << "找到了相邻的重复的元素，值为：" << *ret << std::endl;
    }
    else
    {
        std::cout << "未找到元素" << std::endl;
    }
}

/*
    二分查找
    std::binary_search 算法
    注意：要么在升序的序列，要么在降序的序列。在无序序列不可用
*/
void test05()
{
    std::cout << __func__ << std::endl;
    std::vector<int> v;
    for(int i = 0; i < 10; i++)
    {
        v.push_back(i);
    }

    bool ret = std::binary_search(v.begin(), v.end(), 12);
    if(ret)
    {
        std::cout << "找到了" << std::endl;
    }
    else
    {
        std::cout << "未找到" << std::endl;
    }

}

/*
    std::count 统计值为 3的个数
*/
void test06()
{
    std::vector<int> v; 
    for(int i = 0; i < 10; i++)
    {
        v.push_back(i);
    }
    v.push_back(3);
    v.push_back(3);
    v.push_back(3);
    v.push_back(3);
    
    int num = std::count(v.begin(), v.end(), 3);
    std::cout << "count 3的个数为：" << num << std::endl;
}
/*
    std::count_if 统计值大于等于 3的个数，传递函数对象
*/
class CompareEqAndThan3
{
public:
    bool operator()(int val)
    {
        return val >= 3;
    }
};

void test07()
{
    std::vector<int> v;
    for(int i = 0; i < 10; i++)
    {
        v.push_back(i);
    }
    v.push_back(3);
    v.push_back(3);
    v.push_back(3);
    v.push_back(3);

    int num = std::count_if(v.begin(), v.end(), CompareEqAndThan3());
    std::cout << "count_if 值大于等于 3的个数为：" << num << std::endl;

}

int main(void)
{
    test01();
    std::cout << std::endl;
    test02();

    std::cout << std::endl;
    test03();
    std::cout << std::endl;
    test04();
    std::cout << std::endl;
    test05();
    std::cout << std::endl;
    test06();
    std::cout << std::endl;
    test07();

    return 0;
}
/*

test01
未找到元素

test02
找到元素, 姓名：ddd，年龄：14

test03
匹配到了，姓名：bbb, 年龄: 20

test04
找到了相邻的重复的元素，值为：200

test05
未找到

count 3的个数为：5

count_if 值大于等于 3的个数为：11

*/