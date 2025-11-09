#pragma once
#include <iostream>
#include "student_system.h"
#include "teacher_system.h"
#include "admin_system.h"
#include "schedule_system.h"


class ComputerRoomScheduleSystem : public ScheduleSystem
{
    StudentSideSystem* pStudentSystem;
    TeacherSideSystem* pTeacherSystem;
    AdministrationSideSystem* pAdministractionSystem;

    // method

public:
    ComputerRoomScheduleSystem();
    
    // 显示主菜单
    void DisplayMainMenu();
    
    // 显示子菜单(学生、老师、管理员) 登录页面
    void StudentLogin();
    void TeacherLogin();
    void AdminLogin();

};

