/*

底层容器可以用deque和list。

- deque容器：动态二维数组(头尾两端开口)
- list容器：底层双链表
*/
#include <iostream>
#include <stack>

class Person
{
    friend std::ostream& operator<<(std::ostream& out, Person& person);
    std::string mName;
public:
    Person(std::string name)
    {
        this->mName = name;
        std::cout << this->mName << " Person 构造函数" << std::endl;
    }
    Person(const Person& ref)
    {
        this->mName = ref.mName;
        std::cout << this->mName << " Person 拷贝函数" << std::endl;
    }
    ~Person()
    {
        std::cout << this->mName << " Person 析构函数" << std::endl;
    }

    void showPerson()
    {
        std::cout << "姓名：" << this->mName;
    }
};

std::ostream& operator<<(std::ostream& out, Person& person)
{
    person.showPerson();
    out << std::endl;
    return out;
}

// 构造函数
void test01()
{
    std::cout << __func__ << std::endl;
    Person p1("p1");
    Person p2("p2");
    Person p3("p3");
    Person p4("p4");
    
    std::stack<Person> S;
    S.push(p1);
    S.push(p2);
    S.push(p3);
    S.push(p4);
    while(!S.empty())
    {
        // 访问栈顶元素
        std::cout << S.top() << " " << std::endl;
        // 弹出栈顶元素
        S.pop();
    }
    std::cout << "size: " << S.size() << std::endl;
}
// stack赋值操作  operator=(const stack &stk)
void test02()
{
    std::cout << __func__ << std::endl;
    Person p1("p1");
    Person p2("p2");
    Person p3("p3");
    Person p4("p4");

    std::stack<Person> S;
    S.push(p1);  // push一次 就调用一次拷贝构造
    S.push(p2);
    S.push(p3);
    S.push(p4);

    std::stack<Person> S1;
    S1 = S;  // 调用元素的拷贝构造
    std::cout << "***************  S栈数组如下：* **************" << std::endl;


    while(!S.empty())
    {
        // 访问栈顶元素
        std::cout << S.top() << " " << std::endl;
        // 弹出栈顶元素
        S.pop();  // 自动调用元素对象的析构函数
    }
    std::cout << "size: " << S.size() << std::endl;

    std::cout << "***************  S1 栈数组如下：* **************" << std::endl;

    while(!S1.empty())
    {
        // 访问栈顶元素
        std::cout << S1.top() << " " << std::endl;
        // 弹出栈顶元素
        S1.pop();
    }
}

int main(void)
{
    test01();
    std::cout << std::endl;
    test02();
    return 0;
}

/*

test01
p1 Person 构造函数
p2 Person 构造函数
p3 Person 构造函数
p4 Person 构造函数
p1 Person 拷贝函数
p2 Person 拷贝函数
p3 Person 拷贝函数
p4 Person 拷贝函数
姓名：p4

p4 Person 析构函数
姓名：p3

p3 Person 析构函数
姓名：p2

p2 Person 析构函数
姓名：p1

p1 Person 析构函数
size: 0
p4 Person 析构函数
p3 Person 析构函数
p2 Person 析构函数
p1 Person 析构函数

test02
p1 Person 构造函数
p2 Person 构造函数
p3 Person 构造函数
p4 Person 构造函数
p1 Person 拷贝函数
p2 Person 拷贝函数
p3 Person 拷贝函数
p4 Person 拷贝函数
p1 Person 拷贝函数
p2 Person 拷贝函数
p3 Person 拷贝函数
p4 Person 拷贝函数
***************  S栈数组如下：* **************
姓名：p4

p4 Person 析构函数
姓名：p3

p3 Person 析构函数
姓名：p2

p2 Person 析构函数
姓名：p1

p1 Person 析构函数
size: 0
***************  S1 栈数组如下：* **************
姓名：p4

p4 Person 析构函数
姓名：p3

p3 Person 析构函数
姓名：p2

p2 Person 析构函数
姓名：p1

p1 Person 析构函数
p4 Person 析构函数
p3 Person 析构函数
p2 Person 析构函数
p1 Person 析构函数

*/