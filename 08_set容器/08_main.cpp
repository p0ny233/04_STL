#include <iostream>
#include <set>

template <class T>
void printEle(std::set<T>& s)
{
    std::string type = "int";
    for(class std::set<T>::iterator it = s.begin(); it != s.end(); it++)
    {
        if(type == typeid(T).name())
        {
            std::cout << *it << ", ";
            continue;
        }
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;
}

class Person
{
    friend std::ostream& operator<<(std::ostream& out, const Person& p);

public:
    std::string mName;
    int mAge;

    Person(std::string name, int age)
    {
        this->mName = name;
        this->mAge = age;
        std::cout << this->mName << " Person 构造函数" << std::endl;
    }

    Person(const Person& ref)
    {
        this->mAge = ref.mAge;
        this->mName = ref.mName;
        std::cout << this->mName << "Person 拷贝构造函数" << std::endl;
    }

    ~Person()
    {
        std::cout << this->mName << "Person 析构函数" << std::endl;
    }
};

void test01()
{   
    std::cout << __func__ << std::endl;
    std::set<int> S;
    // 添加数据得用 insert进行插入，如下的值是 无序的
    S.insert(10);
    S.insert(50);
    S.insert(30);
    S.insert(20);
    S.insert(60);

    // 遍历 S
    printEle(S);  // 10, 20, 30, 50, 60,   升序的

    // 判断是否为空
    if(S.empty())
    {
        std::cout << "set 为空" << std::endl;
    }
    else
    {
        std::cout << "set 不为空" << std::endl;
    }

    // 删除元素
    S.erase(30);
    printEle(S);  // 10, 20, 50, 60,   升序的

}

void test02()
{
    std::cout << __func__ << std::endl;
    std::set<int> S;
    // 添加数据得用 insert进行插入，如下的值是 无序的
    S.insert(10);
    S.insert(50);
    S.insert(30);
    S.insert(20);
    S.insert(40);
    S.insert(60);
    S.insert(40);  // 重复插入，set是有唯一性，值为 40 的只能存在一个

    // 从S 里面查找 30元素
    std::set<int>::iterator it = S.find(30);  // find 如果找到元素就 返回元素的迭代器，如果没找到，返回 S.end()
    if(it == S.end())  // 没找到
    {
        std::cout << "未找到元素" << std::endl;
    }
    else
    {
        std::cout << "找到值为30的元素" << std::endl;
    }

    // 统计 元素值为 40 的个数
    printEle(S);
    int n = S.count(40);  // 对于 set，count要么返回0，要么返回 1，因为不允许重复的值
    std::cout << "元素值为 40 的个数为：" << n << std::endl;
}

void test03()
{
    std::cout << __func__ << std::endl;
    std::set<int> S;
    // 添加数据得用 insert进行插入，如下的值是 无序的
    S.insert(10);
    S.insert(50);
    S.insert(30);
    S.insert(20);
    S.insert(40);
    S.insert(60);

    // lower_bound
    // 返回一个指向当前 set 容器中第一个大于等于 (20)val 的元素的双向迭代器。
    std::set<int>::iterator pos = S.lower_bound(20);  // 没有匹配到就返回 S.end()
    if(pos != S.end())
    {
        std::cout << "lower_bound的值为: " << *pos << std::endl;
    }
    else
    {
        std::cout << "lower_bound 不匹配" << std::endl;
    }

    // upper_bound
    // 返回一个指向当前 set 容器中第一个大于(30)val 的元素的双向迭代器。
    std::set<int>::iterator pos2 = S.upper_bound(30);  // 没有匹配到就返回 S.end()
    if(pos2 != S.end())
    {
        std::cout << "upper_bound的值为: " << *pos2 << std::endl;
    }
    else
    {
        std::cout << "upper_bound 不匹配" << std::endl;
    }
}

// equal_range(keyEle)  
// 该方法将返回一个范围，第一个是 lower_bound的值，第二个是 upper_bound的值

// 该范围中包含的值为 keyEle 的元素（set 容器中各个元素是唯一的，因此该范围最多包含一个元素）
void test04()
{
    std::cout << __func__ << std::endl;
    std::set<int> S;
    // 添加数据得用 insert进行插入，如下的值是 无序的
    S.insert(10);
    S.insert(50);
    S.insert(30);
    S.insert(20);
    S.insert(40);
    S.insert(60);

    std::pair<std::set<int>::iterator, std::set<int>::iterator> pairs = S.equal_range(30);
    if (pairs.first != S.end())
        std::cout << "pairs.first: " << *pairs.first << std::endl;
    else
        std::cout << "pairs.first: " << "未找到" << std::endl;

    if (pairs.second != S.end())
        std::cout << "pairs.second: " << *pairs.second << std::endl;
    else
        std::cout << "pairs.second: " << "未找到" << std::endl;
}

// insert返回值，验证set插入值是否成功
void test05()
{
    std::cout << __func__ << std::endl;
    std::set<int> S;
    std::pair<std::set<int>::iterator, bool> ret = S.insert(10);  // 查看返回值的类型 pair<iterator, bool>，对组得第二个就表示插入成功与否
    if(ret.second)
    {
        std::cout << "第一次插入成功" << std::endl;
    }
    else
    {
        std::cout << "第一次插入失败" << std::endl;
    }

    ret = S.insert(10);  // 查看返回值的类型 pair<iterator, bool>，对组得第二个就表示插入成功与否
    if(ret.second)
    {
        std::cout << "第二次插入成功" << std::endl;
    }
    else
    {
        std::cout << "第二次插入失败" << std::endl;
    }
}

// 使用 multilset 插入重复的值 
void test06()
{   
    std::cout << __func__ << std::endl;
    std::multiset<int> mset;
    mset.insert(10);  // 可以看到 multilset的insert定义，仅返回 迭代器
    mset.insert(10);

    for(class std::multiset<int>::iterator it = mset.begin(); it != mset.end(); it++)
    {
        std::cout << *it << " "; 
    }
    std::cout << std::endl;
}

// 修改 set的默认排序规则,默认是升序，修改为 降序
class MyCompareInt
{
public:
    bool operator()(int v1, int v2)const
    {
        return v1 > v2;
    }
};
void test07()
{
    std::cout << __func__ << std::endl;
    //在创建 set的时候，
    std::set<int, MyCompareInt> S;
    S.insert(10);
    S.insert(50);
    S.insert(30);
    S.insert(20);
    S.insert(40);
    S.insert(60);
    
    for(std::set<int, MyCompareInt>::iterator it = S.begin(); it != S.end(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;


}

// 对于自定义类型的数据的排序规则

std::ostream& operator<<(std::ostream& out, const Person& p)
{
    out << "姓名：" << p.mName << ", 年龄：" << p.mAge << std::endl;
    return out;
}


class MyComparePerson
{
public:
    bool operator()(const Person& p1, const Person& p2)const
    {
        return p1.mAge > p2.mAge;  // 按照年龄从大到小 排序
    }
};

void test08()
{
    std::cout << __func__ << std::endl;
    //在创建 set的时候，排序规则指定为 ： MyComparePerson
    std::set<Person, MyComparePerson> S;
    Person p1("aaa", 10);
    Person p2("bbb", 40);
    Person p3("ccc", 20);
    Person p4("ddd", 30);
    Person p5("eee", 50);

    S.insert(p1);
    S.insert(p2);
    S.insert(p3);
    S.insert(p4);
    S.insert(p5);

    for(std::set<Person, MyComparePerson>::iterator it = S.begin(); it != S.end(); it++)
    {
        std::cout << *it;
    }
    

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
    std::cout << std::endl;
    test08();
    std::cout << std::endl;
    return 0;
}

/*

test01
10, 20, 30, 50, 60,
set 不为空
10, 20, 50, 60,

test02
找到值为30的元素
10, 20, 30, 40, 50, 60,
元素值为 40 的个数为：1

test03
lower_bound的值为: 20
upper_bound的值为: 40

test04
pairs.first: 30
pairs.second: 40

test05
第一次插入成功
第二次插入失败

test06
10 10

test07
60 50 40 30 20 10

test08
aaa Person 构造函数
bbb Person 构造函数
ccc Person 构造函数
ddd Person 构造函数
eee Person 构造函数
aaaPerson 拷贝构造函数
bbbPerson 拷贝构造函数
cccPerson 拷贝构造函数
dddPerson 拷贝构造函数
eeePerson 拷贝构造函数
姓名：eee, 年龄：50
姓名：bbb, 年龄：40
姓名：ddd, 年龄：30
姓名：ccc, 年龄：20
姓名：aaa, 年龄：10
eeePerson 析构函数
dddPerson 析构函数
cccPerson 析构函数
bbbPerson 析构函数
aaaPerson 析构函数
aaaPerson 析构函数
cccPerson 析构函数
dddPerson 析构函数
bbbPerson 析构函数
eeePerson 析构函数

*/