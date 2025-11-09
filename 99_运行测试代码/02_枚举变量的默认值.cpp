#include <iostream>
enum IdentifyType
{
    Student, Teacher, Admin
};
void test02()
{
    //enum IdentifyType identify;
    //std::cout << identify << std::endl;  // 编译器报错，因为 identify 没有被赋值/初始化
}

int main2(void)
{
    test02();
    return 0;
}