#include "utils.h"

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

void LogUtils::LOGI(std::string msg)
{
    if (DEBUG)
        std::cout << __func__ << ", " << msg << std::endl;
}
bool LogUtils::DEBUG = true;
