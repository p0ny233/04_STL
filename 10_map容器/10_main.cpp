#include <iostream>
#include <map>

// 使用 insert 往 map添加数据
void test01()
{
    std::cout << __func__ << std::endl;
    std::map<int, int> mp;
    // 第一种插入方式
    mp.insert(std::pair<int, int>(1, 10));

    // 第二种插入方式 (推荐)
    mp.insert(std::make_pair(2, 20));

    // 第三种插入方式
    mp.insert(std::map<int, int>::value_type(3,30));
    
    // 第四种，有隐患
    mp[4] = 40;

    std::cout << mp[5] << std::endl;  // 如果map中没有 键5，那么会插入 键5值0的元素，如果
    

    // 遍历
    for(std::map<int, int>::iterator it = mp.begin(); it != mp.end(); it++)
    {
        std::cout << "key: " << it->first << ", value: " << it->second << std::endl;
    }
}

// 删除
void test02()
{
    std::cout << __func__ << std::endl;
    std::map<int, int> mp;
    mp.insert(std::pair<int, int>(1, 10));
    mp.insert(std::make_pair<int, int>(2, 20));
    mp.insert(std::map<int, int>::value_type(3, 30));
    mp[4] = 40;

    for(std::map<int, int>::iterator it = mp.begin(); it != mp.end(); it++)
    {
        std::cout << "key: " << it->first << ", value: " << it->second << std::endl;
    }

    std::map<int, int>::iterator reIt = mp.erase(mp.begin());  // 给定一个迭代器，删除该迭代器的元素
    std::cout << reIt->first << std::endl;  // 2

    std::cout << "元素删除后：" << std::endl;
    for(std::map<int, int>::iterator it = mp.begin(); it != mp.end(); it++)
    {
        std::cout << "key: " << it->first << ", value: " << it->second << std::endl;
    }
    std::cout << "删除键为 3 的对组后: " << std::endl;
    mp.erase(3);  // 删除键为 3 的对组

    for(std::map<int, int>::iterator it = mp.begin(); it != mp.end(); it++)
    {
        std::cout << "key: " << it->first << ", value: " << it->second << std::endl;
    }
        
    mp.insert(std::make_pair(5, 50));
    mp.insert(std::make_pair(6, 60));
    mp.insert(std::make_pair(7, 70));
    std::cout << "mp 添加数据后: " << std::endl;
    for(std::map<int, int>::iterator it = mp.begin(); it != mp.end(); it++)
    {
        std::cout << "key: " << it->first << ", value: " << it->second << std::endl;
    }

    std::cout << "size: " << mp.size() << std::endl;

    // 删除 指定区间的所有元素
    mp.erase(mp.begin(), mp.end());
    std::cout << "size: " << mp.size() << std::endl;
    
    

}

// 查找
void test03()
{
    std::cout << __func__ << std::endl;
    std::map<int, int> mp;
    mp.insert(std::pair<int, int>(1, 10));
    mp.insert(std::make_pair<int, int>(2, 20));
    mp.insert(std::map<int, int>::value_type(3, 30));
    mp[4] = 40;

    // find(key);  根据key查找元素，找到返回迭代器，未找到则返回 map.end()
    std::map<int, int>::iterator reIt = mp.find(3);
    if(reIt != mp.end())
    {
        std::cout << "找到元素，" << "key: " << reIt->first << ", value: " << reIt->second << std::endl;
    }
    else
    {
        std::cout << "未找到元素" << std::endl;
    }

    // 统计
    int n = mp.count(4);  // 对于map，统计key的个数要么是0要么1.同set
    std::cout << "统计key为4的对组个数：" << n << std::endl;
    
    // lower_bound，返回 iterator，找到第一个 大于等于 key的迭代器
    reIt = mp.lower_bound(3);
    if(reIt != mp.end())
    {
        std::cout << "lower_bound, key: " << reIt->first << ", value: " << reIt->second << std::endl;
    }
    else
    {
        std::cout << "lower_bound, 未找到" << std::endl;
    }

    // upper_bound
    // upper_bound，返回 iterator，找到第一个 大于 key的迭代器

    reIt = mp.upper_bound(3);
    if(reIt != mp.end())
    {
        std::cout << "upper_bound, key: " << reIt->first << ", value: " << reIt->second << std::endl;
    }
    else
    {
        std::cout << "upper_bound, 未找到" << std::endl;
    }

    // equal_range， 返回类型pair<iterator, iterator>，
    // 第一个是 大于等于 _Key 的迭代器(相当于 lower_bound)，
    // 第二个是 大于 _Key 的迭代器(相当于 upper_bound)
    std::pair<std::map<int,int>::iterator, std::map<int,int>::iterator> ret = mp.equal_range(3);
    if(ret.first != mp.end())
    {
        // 找到了
        std::cout << "equal_range first, key: " << ret.first->first << ", value: " << ret.first->second << std::endl;
    }
    else
    {
        std::cout << "equal_range first 未找到" << std::endl;
    }    
    if(ret.second != mp.end())
    {
        // 找到了
        std::cout << "equal_range second, key: " << ret.second->first << ", value: " << ret.second->second << std::endl;
    }
    else
    {
        std::cout << "equal_range second 未找到" << std::endl;
    }

}

// 修改排序规则
class MycompareInt
{
public:
    bool operator()(int v1, int v2) const  // 要加const才可以
    {
        return v1 < v2;
    }
};

void test04()
{
    std::cout << __func__ << std::endl;
    std::map<int, int, MycompareInt> mp;
    mp.insert(std::pair<int, int>(1, 10));
    mp.insert(std::make_pair<int, int>(2, 20));
    mp.insert(std::map<int, int>::value_type(3, 30));
    mp[4] = 40;

    for(std::map<int, int, MycompareInt>::iterator it = mp.begin(); it != mp.end(); it++)
    {
        std::cout << "key: " << it->first << ", value: " << it->second << std::endl;
    }
    
}

// 如果容器存储 自定义数据类型对象的指针，当容器清除所有的元素时，是否会通过指针 调用 自定义数据类型对象的析构函数?  
// 答：不会，换成使用 std::shared_ptr 来管理内存
class Person
{
    std::string mName;

public:
    Person(std::string name) : mName(name)
    {
        std::cout << this->mName << ", Person 构造函数" << std::endl;
    }

    ~Person()
    {
        std::cout << this->mName << ", Person 析构函数" << std::endl;
    }
};

void test05()
{
    std::map<int, std::shared_ptr<Person>> mp;
    std::shared_ptr<Person> p = std::make_unique<Person>("A");

    // 写法一、
     mp.insert(std::make_pair(1, (p)));
    // 写法二、
    //std::pair<int, std::shared_ptr<Person>> p1 = std::make_pair(1, (p));  // 额外的中间变量
    //mp.insert((p1));  // 传递时要使用 move，转移控制权，没有move会发生拷贝构造，shared_ptr禁用了拷贝构造
    // ()的返回值 是右值中的 将亡值，右值。
    // 写法一的 make_pair 返回值就是临时对象，触发的 移动构造
 
    mp.clear();  // 清除元素的同时，会调用自定义类型数据的析构
    getchar();
    
}

int main(void)
{
    //test01();
    //std::cout << std::endl;
    //test02();

    //std::cout << std::endl;
    //test03();

    //std::cout << std::endl;
    //test04();

    std::cout << std::endl;
    test05();

    return 0;
}

/*

test01
0
key: 1, value: 10
key: 2, value: 20
key: 3, value: 30
key: 4, value: 40
key: 5, value: 0

test02
key: 1, value: 10
key: 2, value: 20
key: 3, value: 30
key: 4, value: 40
2
元素删除后：
key: 2, value: 20
key: 3, value: 30
key: 4, value: 40
删除键为 3 的对组后:
key: 2, value: 20
key: 4, value: 40
mp 添加数据后:
key: 2, value: 20
key: 4, value: 40
key: 5, value: 50
key: 6, value: 60
key: 7, value: 70
size: 5
size: 0

test03
找到元素，key: 3, value: 30
统计key为4的对组个数：1
lower_bound, key: 3, value: 30
upper_bound, key: 4, value: 40
equal_range first, key: 3, value: 30
equal_range second, key: 4, value: 40

test04
key: 1, value: 10
key: 2, value: 20
key: 3, value: 30
key: 4, value: 40

*/