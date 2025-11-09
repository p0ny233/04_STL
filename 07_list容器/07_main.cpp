/*
    
    1. 遍历 iterator(正序)、reverse_iterator(逆序)
    2. 尾插 push_back、头插 push_front
    3. 插入 insert、删除 erase(接收迭代器)、remove(根据元素值删除，如果元素是自定义数据类型，那么需要重载 operator==(const &T val)const{}    )
*/
#include <iostream>
#include <list>
#include <algorithm>

template <class T>
void printList(std::list<T>& list)
{
    // https://blog.csdn.net/2302_79031646/article/details/140928069
    //for(std::list<T>::iterator it = list.begin(); it != list.end(); it++)
    // 15 行代码没报红，但编译时报错

    for(typename std::list<T>::iterator it = list.begin(); it != list.end(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

bool myCompareInt(int a, int b)
{
    return a > b;
}



class Person
{
    friend std::ostream& operator<<(std::ostream& out, Person& ref);
public:
    std::string mName;
    int mAge;
    int mHeight;  // 身高

    Person(std::string name, int age, int height)
    {
        this->mName = name;
        this->mAge = age;
        this->mHeight = height;
        std::cout << this->mName << ", Person 构造函数" << std::endl;
    }
    Person(const Person& ref)
    {
        this->mName = ref.mName;
        this->mAge = ref.mAge;
        this->mHeight = ref.mHeight;
        std::cout << this->mName << ", Person 拷贝构造函数" << std::endl;
    }

    ~Person()
    {
        std::cout << this->mName << ", Person 析构函数" << std::endl;
    }

    //bool operator==(const Person& p)  // 报错
    /*
        没有找到接受“const _Ty”类型的右操作数的运算符(或没有可接受的转换)
    */
    bool operator==(const Person& p) const  // 两个const都不能丢，否则报错
    {
        if (this->mName == p.mName && this->mAge == p. mAge && this->mHeight == p.mHeight)
            return true;
        return false;
    }
};

std::ostream& operator<<(std::ostream& out, Person& ref)
{
    out << "姓名: " << ref.mName << ", 年龄: " << ref.mAge << ", 身高：" << ref.mHeight << std::endl;
    return out;
}


bool myComparePerson(const Person& p1, const Person& p2)
{
    return p1.mAge > p2.mAge;
}

bool myComparePerson1(const Person& p1, const Person& p2)
{
    if(p1.mAge == p2.mAge)
    {
        // 年龄相同，比较身高
        return p1.mHeight > p2.mHeight;
    
    }
    return p1.mAge > p2.mAge;
}


// 1. 遍历 iterator(正序)、reverse_iterator(逆序)
void test01()
{
    
    std::cout << __func__ << std::endl;
    std::list<int> List;
    List.push_back(10);
    List.push_back(20);
    List.push_back(30);
    
    // 正序遍历
    for(std::list<int>::iterator it = List.begin(); it != List.end(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    // 逆序遍历
    for(std::list<int>::reverse_iterator it = List.rbegin(); it != List.rend(); it++)
    {
        std::cout << *it << " ";
    }
}

// 2. 尾插 push_back、头插 push_front
void test02()
{
    std::cout << __func__ << std::endl;
    std::list<int> List;
    // 尾插
    List.push_back(10);
    List.push_back(20);
    List.push_back(30);
    // 头插
    List.push_front(100);
    List.push_front(102);
    List.push_front(101);
    // 101 102 100 10 20 30 

    printList(List);
}

// 3. 插入 insert、删除 erase(接收迭代器)、remove(根据元素值删除)
void test03()
{
    std::cout << __func__ << std::endl;
    std::list<int> List;
    List.push_back(10);
    List.push_back(20);
    List.push_back(30);
    List.push_front(100);
    List.push_front(100);
    List.push_front(101);

    List.insert(List.begin(), 6666);
    printList(List);  // 6666 101 100 100 10 20 30

    List.erase(List.begin());  // erase 接收迭代器
    printList(List);  // 101 100 100 10 20 30

    // 删除容器中，所有与100值 匹配的元素
    List.remove(100);  // 删除值为 100的元素(有几个100就删除几个100)
    printList(List);  // 101 10 20 30
}

// 4. 赋值操作 assign、互换 swap
void test04()
{
    std::cout << __func__ << std::endl;
    std::list<int> list01;
    list01.push_back(10);
    list01.push_back(20);
    list01.push_back(30);
    list01.push_front(100);
    list01.push_front(100);
    list01.push_front(101);
    
    std::list<int> list02;
    list02.assign(10, 100);  // 10个100
    printList(list02); // 100 100 100 100 100 100 100 100 100 100
    
    // swap 互换
    list01.swap(list02);
    printList(list02);  // 101 100 100 10 20 30

}

// 5. 反转排序， 反转 reverse、排序 sort
void test05()
{
    std::cout << __func__ << std::endl;
    std::list<int> list01;
    list01.push_back(10);
    list01.push_back(20);
    list01.push_back(30);
    list01.push_front(100);
    list01.push_front(100);
    list01.push_front(101);
    printList(list01);
    list01.reverse();  // 反转
    std::cout << "反转后:" << std::endl;
    printList(list01);


    // 排序
    //sort(list01.begin(), list01.end());  // 报错，sort是全局函数
    //printList(list01);
    /*
        规则：如果这个容器支持随机访问，那么可以使用系统提供的标准算法
                不支持随机访问的迭代器的容器，内部会提供对应的算法接口sort
    */

    list01.sort();
    std::cout << "默认从小到大 排序:" << std::endl;
    printList(list01);
    
    std::cout << "指定为从大到小 排序:" << std::endl;
    list01.sort(myCompareInt);
    printList(list01);
}

// 6. 对成员函数sort的深度使用
void test06()
{
    std::cout << __func__ << std::endl;
    std::list<Person> list01;
    Person p1("aaa", 40, 200);
    Person p2("bbb", 20, 180);
    Person p3("ccc", 30, 120);
    Person p4("ddd", 50, 160);
    Person p5("eee", 10, 170);
    Person p6("fff", 10, 165);
    Person p7("ggg", 10, 185);


    list01.push_back(p1);
    list01.push_back(p2);
    list01.push_back(p3);
    list01.push_back(p4);
    list01.push_back(p5);
    list01.push_back(p6);
    list01.push_back(p7);

    // 按照年龄降序(从大到小)
    list01.sort(myComparePerson);
    printList<Person>(list01);
    
    // 再给 Person加个属性，身高，如果年龄相同，那么就对身高排序，高的在前面
    std::cout << "优先比较年龄，后比较身高: " << std::endl;
    list01.sort(myComparePerson1);
    printList<Person>(list01);
}

// 7. 删除元素 remove
void test07()
{
    std::cout << __func__ << std::endl;
    std::list<Person> list01;
    Person p1("aaa", 40, 200);
    Person p2("bbb", 20, 180);
    Person p3("ccc", 30, 120);
    Person p4("ddd", 50, 160);
    Person p5("eee", 10, 170);
    Person p6("fff", 10, 165);
    Person p7("ggg", 10, 185);

    list01.push_back(p1);
    list01.push_back(p2);
    list01.push_back(p3);
    list01.push_back(p4);
    list01.push_back(p5);
    list01.push_back(p6);
    list01.push_back(p7);

    std::cout << "\n删除 ddd 后: " << std::endl;;
    list01.remove(p4);  // 需要重载 自定义数据类型Person的 operator== 运算符
    printList(list01);


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
10 20 30
30 20 10
test02
101 102 100 10 20 30

test03
6666 101 100 100 10 20 30
101 100 100 10 20 30
101 10 20 30

test04
100 100 100 100 100 100 100 100 100 100
101 100 100 10 20 30

test05
101 100 100 10 20 30
反转后:
30 20 10 100 100 101
默认从小到大 排序:
10 20 30 100 100 101
指定为从大到小 排序:
101 100 100 30 20 10

test06
aaa, Person 构造函数
bbb, Person 构造函数
ccc, Person 构造函数
ddd, Person 构造函数
eee, Person 构造函数
fff, Person 构造函数
ggg, Person 构造函数
aaa, Person 拷贝构造函数
bbb, Person 拷贝构造函数
ccc, Person 拷贝构造函数
ddd, Person 拷贝构造函数
eee, Person 拷贝构造函数
fff, Person 拷贝构造函数
ggg, Person 拷贝构造函数
姓名: ddd, 年龄: 50, 身高：160
 姓名: aaa, 年龄: 40, 身高：200
 姓名: ccc, 年龄: 30, 身高：120
 姓名: bbb, 年龄: 20, 身高：180
 姓名: eee, 年龄: 10, 身高：170
 姓名: fff, 年龄: 10, 身高：165
 姓名: ggg, 年龄: 10, 身高：185

优先比较年龄，后比较身高:
姓名: ddd, 年龄: 50, 身高：160
 姓名: aaa, 年龄: 40, 身高：200
 姓名: ccc, 年龄: 30, 身高：120
 姓名: bbb, 年龄: 20, 身高：180
 姓名: ggg, 年龄: 10, 身高：185
 姓名: eee, 年龄: 10, 身高：170
 姓名: fff, 年龄: 10, 身高：165

ggg, Person 析构函数
fff, Person 析构函数
eee, Person 析构函数
ddd, Person 析构函数
ccc, Person 析构函数
bbb, Person 析构函数
aaa, Person 析构函数
ddd, Person 析构函数
aaa, Person 析构函数
ccc, Person 析构函数
bbb, Person 析构函数
ggg, Person 析构函数
eee, Person 析构函数
fff, Person 析构函数

test07
aaa, Person 构造函数
bbb, Person 构造函数
ccc, Person 构造函数
ddd, Person 构造函数
eee, Person 构造函数
fff, Person 构造函数
ggg, Person 构造函数
aaa, Person 拷贝构造函数
bbb, Person 拷贝构造函数
ccc, Person 拷贝构造函数
ddd, Person 拷贝构造函数
eee, Person 拷贝构造函数
fff, Person 拷贝构造函数
ggg, Person 拷贝构造函数

删除 ddd 后:
ddd, Person 析构函数
姓名: aaa, 年龄: 40, 身高：200
 姓名: bbb, 年龄: 20, 身高：180
 姓名: ccc, 年龄: 30, 身高：120
 姓名: eee, 年龄: 10, 身高：170
 姓名: fff, 年龄: 10, 身高：165
 姓名: ggg, 年龄: 10, 身高：185

ggg, Person 析构函数
fff, Person 析构函数
eee, Person 析构函数
ddd, Person 析构函数
ccc, Person 析构函数
bbb, Person 析构函数
aaa, Person 析构函数
aaa, Person 析构函数
bbb, Person 析构函数
ccc, Person 析构函数
eee, Person 析构函数
fff, Person 析构函数
ggg, Person 析构函数

*/