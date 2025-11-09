#pragma once
#include <iostream>
class Employee
{
public:
    std::string mName;  // 姓名
    int mAge;           // 年龄
    double mSalary;     // 薪水

    Employee(std::string name, int age, double salary) : mName(name), mAge(age), mSalary(salary) {}

};

