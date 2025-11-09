/*
    教师端
*/
#pragma once
#include "account_system.h"

class TeacherSideSystem : public AccountSystem
{
private:
    // attr
    std::map<AuditOptionTypes, std::string> optionMap;

    // 0. 登录
    bool __Login();

    bool __DisplayAnyMenu();

    bool DisplayCanCanCelItem();

public:
    TeacherSideSystem();
    

    // 0. 登录
    void Login(int type);
    // 1. 查看所有预约
    void ViewAllAppointment();
    // 2. 审核预约
    void ReviewAppointment();
};