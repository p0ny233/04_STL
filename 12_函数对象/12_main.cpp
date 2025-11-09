#include <iostream>

class MyPrint
{
public:
    int count = 0;
    void operator()(int num)  // 有一个参数，称为一元仿函数，2个参数，称为二元仿函数
    {
        std::cout << num << std::endl;
        count++;
    }
};

int main(void)
{
    MyPrint myPrint;
    myPrint(100);
    myPrint(101);
    myPrint(102);
    myPrint(103);
    std::cout << "调用次数: " << myPrint.count << std::endl;
    
    return 0;
}
