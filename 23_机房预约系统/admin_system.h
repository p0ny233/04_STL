#pragma once
#include "account_system.h"

class AdministrationSideSystem : public ManagerAccountSystem
{
private:
    // attr
    ComputerRoomSystem* pComputerRoomSystem = nullptr;

    // methods
    bool __DisplayAnyMenu();
    bool __Login();
    bool __AddUserFor();
    bool __ViewUsers(int op);
    bool __ClearStudentAccount();

    bool __ClearTeacherAccount();
    
    bool __ViewComputerRoomDetail();


public:
    AdministrationSideSystem();
    ~AdministrationSideSystem();

    // 0. 登录
    void Login(int type);

    // 1. 添加账号(学生还是老师)
    void AddUserFor();

    // 2. 查看账号(学生还是老师)
    void ViewUsers();
    
    // 3. 查看机房(显示机房编号以及最大容量
    void ViewComputerRoomDetail();

    // 4. 清空预约
    void ClearAppointment();


    // 清空账户


    void ClearStudentAccount();

    void ClearTeacherAccount();

};