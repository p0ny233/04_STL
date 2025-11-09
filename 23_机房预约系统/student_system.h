/*
    学生端
*/
#pragma once
#include "account_system.h"
#include <algorithm>
#include "appointment_reord.h"
#include "utils.h"

class StudentSideSystem : public EducationAccountSystem
{

private:
    bool VerifyUser(std::string& user_account, std::string& pwd);
    // 0. 登录
    bool __Login();
    // 显示成功登录后的菜单
    //void DisplayAnyMenu();
    bool __DisplayAnyMenu();

    // 1. 申请预约 私有接口
    bool __AppointmentApplication();
    // 2. 查看我的预约
    bool __ViewMyAppointment();

    // 3. 取消预约
    bool __CancelAppointment(int idx);
    
public:

    // 构造
    StudentSideSystem();

    // 0. 登录
    void Login(int);
    // 1. 申请预约
    void AppointmentApplication();
    // 2. 查看我的预约
    void ViewMyAppointment();
    // 3. 查看所有预约
    void ViewALLPointment();
    // 4. 取消预约
    void CancelAppointment();
};

enum WEEKEN
{
     Mon, Tue, Wes, Thi, Fri
};