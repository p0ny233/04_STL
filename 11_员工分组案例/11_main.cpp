#include <iostream>
#include <map>
#include <set>
#include "worker.h"
#include "partment.h"

Employee* createWorker(std::string name, int age, double salary)
{
    return new Employee(name, age, salary);
}

// 显示部门员工信息
template <class T>
void showEmp(std::multimap<int, T>& mp,std::set<int> *partments, bool filter = false)
{
    std::set<int> &refSet = *partments;

    std::string name;
    int age = 0;
    double salary = 0.0;
    std::string partment;

    if(filter)
    {
        // 指定匹配哪几个部门
        for(std::set<int>::iterator it = refSet.begin(); it != refSet.end(); it++)
        {
            // 返回 具体部门的所有员工
            std::pair<std::multimap<int , Employee*>::iterator, std::multimap<int, Employee*>::iterator> its = mp.equal_range(*it);
            // its 相当于 二维数组，元素都是 pair类型的指针

            switch(its.first->first)
            {
            case DEVELOP_DEPARTMENT:
                partment = "研发部";
                break;
            case FINANCEMENT_DEPARTMENT:
                partment = "财务部";
                break;
            case STRATEGY_DEPARTMENT:
                partment = "策划部";
                break;
            }
            std::cout << "如下是【" << partment << "】的员工信息：" << std::endl;
            for(std::multimap<int, Employee*>::iterator fst = its.first; fst != its.second; fst++)
            {  // fst  是 pair类型的指针, 结构相当于 <int, emp>.
               // [ [<int, emp>pair指针, <int, emp>pair指针], [<int, emp>pair指针, <int, emp>pair指针] ]

                std::cout << "姓名: "  << fst->second->mName << ", 年龄: " << fst->second->mAge << std::endl;
            }

            std::cout << std::endl;
        }
    }
    else
    {
        for(class std::multimap<int, T>::iterator it = mp.begin(); it != mp.end(); it++)
        {
            switch(it->first)
            {
                case DEVELOP_DEPARTMENT:
                    partment = "研发部";
                    break;
                case FINANCEMENT_DEPARTMENT:
                    partment = "财务部";
                    break;
                case STRATEGY_DEPARTMENT:
                    partment = "策划部";
                    break;
            }
            std::cout << "隶属部门: " << partment << ", 姓名：" << it->second->mName
                << ", 年龄: " << it->second->mAge
                << ", 薪水: " << it->second->mSalary << std::endl;
        }
            std::cout << std::endl;
    }
}

void test()
{   
    // 0.创建存储
    std::multimap<int, Employee*> mp;
    //std::map<int, Employee*> mp;
    // 1. 创建员工并存入
    mp.insert(std::make_pair<int, Employee*>(DEVELOP_DEPARTMENT, createWorker("赵一鸣", 30, 301.2)));
    mp.insert(std::make_pair<int, Employee*>(FINANCEMENT_DEPARTMENT, createWorker("张三", 12, 301.2)));
    mp.insert(std::make_pair<int, Employee*>(STRATEGY_DEPARTMENT, createWorker("李四", 14, 400.2)));
    mp.insert(std::make_pair<int, Employee*>(FINANCEMENT_DEPARTMENT, createWorker("王五", 8, 201.2)));
    mp.insert(std::make_pair<int, Employee*>(STRATEGY_DEPARTMENT, createWorker("老六", 10, 501.2)));

    // 2. 分部门展示员工信息
    std::set<int> S;
    S.insert(STRATEGY_DEPARTMENT);
    S.insert(FINANCEMENT_DEPARTMENT);
    showEmp(mp, &S, true);

}


int main(void)
{
    test();
    return 0;
}


/*

如下是【财务部】的员工信息：
姓名: 张三, 年龄: 12
姓名: 王五, 年龄: 8

如下是【策划部】的员工信息：
姓名: 李四, 年龄: 14
姓名: 老六, 年龄: 10

*/