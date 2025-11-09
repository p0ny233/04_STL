#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <sstream>


std::string getCurrentTime()
{
    std::stringstream ss;   // 创建stringstream对象ss，需要包含<sstream>头文件。
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    __time64_t tt = std::chrono::system_clock::to_time_t(now);
    struct tm Tm = { 0 };
    localtime_s(&Tm, &tt);
    std::_Timeobj<char, const tm*> tobj = std::put_time(&Tm, "%Y-%m-%d %H:%M:%S");
    ss << tobj;
    std::string timestr = ss.str();     // 把ss转换成string的对象。
    return timestr;
}

// 获取当前时间
void test01()
{
    std::cout << __func__  <<", 获取当前时间" << std::endl;
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    __time64_t tt = std::chrono::system_clock::to_time_t(now);
    struct tm Tm = { 0 };
    localtime_s(&Tm, &tt);
    std::_Timeobj<char, const tm*> obj = std::put_time(&Tm, "%Y-%m-%d %H:%M:%S");
    std::cout << "obj: " << obj << std::endl;  // 可以输出北京时间，但是字符串没法保存


    // 下面的代码就是提取 北京时间字符串，然后存储到std:;string类型的变量中
    std::stringstream ss;   // 创建stringstream对象ss，需要包含<sstream>头文件。
    ss << std::put_time(&Tm, "%Y-%m-%d %H:%M:%S");    // 把时间输出到对象ss中。
    std::string timestr = ss.str();     // 把ss转换成string的对象。
    std::cout << "timestr: " << timestr << std::endl;


    // getCurrentTime() 获取北京时间 字符串
    std::cout << "getCurrentTime(): " << getCurrentTime() << std::endl;
}

int main1(void)
{
    test01();
    return 0;
}

/*

test01, 获取当前时间
obj: 2025-11-03 19:40:25
timestr: 2025-11-03 19:40:25
*/