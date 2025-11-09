#pragma once
#include <iostream>

class Config
{
public:
    Config();
    static std::string ComputerRoomDetailFileName;
    static std::string AppointRecordFileName;
    static std::string StudentAccountFileName;
    static std::string TeacherAccountFileName;
    static std::string AdminAccountFileName;
};

