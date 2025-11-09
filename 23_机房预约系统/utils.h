#pragma once
#include <iostream>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>

std::string getCurrentTime();

class LogUtils
{
    static bool DEBUG;

public:
    static void LOGI(std::string msg);
};


