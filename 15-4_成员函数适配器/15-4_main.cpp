#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

class Person
{
public:
    std::string mName;
    int mAge;
    Person(std::string name, int age) : mName(name), mAge(age){}

    void showInfo()
    {
        std::cout << "成员函数-> 姓名: " << this->mName << ", 年龄：" << this->mAge << std::endl;
    }
};

// 普通函数输出信息
void myPrint(Person& p)
{
    std::cout << "普通函数-> 姓名: " << p.mName << ", 年龄：" << p.mAge << std::endl;
}

void test01()
{
    Person p1("aaa", 10);
    Person p2("bbb", 11);
    Person p3("ccc", 12);
    Person p4("ddd", 13);
    Person p5("eee", 14);
    Person p6("fff", 15);

    std::vector<Person> v;
    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    v.push_back(p4);
    v.push_back(p5);
    v.push_back(p6);

    for_each(v.begin(), v.end(), myPrint);
   
}

// 希望使用 成员函数来输出 Person信息
void test02()
{

    Person p1("aaa", 10);
    Person p2("bbb", 11);
    Person p3("ccc", 12);
    Person p4("ddd", 13);
    Person p5("eee", 14);
    Person p6("fff", 15);

    std::vector<Person> v;
    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    v.push_back(p4);
    v.push_back(p5);
    v.push_back(p6);

    for_each(v.begin(), v.end(), std::mem_fun_ref(&Person::showInfo));
    // mem_fun_ref 内部是 用 类成员函数的指针 调用类的成员函数
}

int main(void)
{
    test01();
    std::cout << std::endl;
    test02();
    return 0;
}
/*

普通函数-> 姓名: aaa, 年龄：10
普通函数-> 姓名: bbb, 年龄：11
普通函数-> 姓名: ccc, 年龄：12
普通函数-> 姓名: ddd, 年龄：13
普通函数-> 姓名: eee, 年龄：14
普通函数-> 姓名: fff, 年龄：15

成员函数-> 姓名: aaa, 年龄：10
成员函数-> 姓名: bbb, 年龄：11
成员函数-> 姓名: ccc, 年龄：12
成员函数-> 姓名: ddd, 年龄：13
成员函数-> 姓名: eee, 年龄：14
成员函数-> 姓名: fff, 年龄：15

*/