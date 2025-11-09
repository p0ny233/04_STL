#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include "config.h"
#include "user.h"
#include "appointment_reord.h"
#include "computer_room_system.h"

// 抽象类
class AccountSystem : public User
{
private:
    bool CheckState();
protected:
    std::map<int, enum IdentifyType> IdentifyMap1;
    std::map<enum IdentifyType, std::string> IdentifyMap2;

    // 记录操作类
    EduAppointmentRecordOperatorAb* pRecordOperator = nullptr;
    enum IdentifyType identify;  // 身份：学生、教师、管理员
    bool isOnline;

    // 共同操作
    virtual bool __Login() = 0;   // 接口，子类实现
    bool Login(int);  // 父类实现  统一 调用 __Login()

    virtual bool __DisplayAnyMenu() = 0;   // 接口，子类实现
    void DisplayAnyMenu();     // 父类实现  统一 调用 __DisplayAnyMenu()
    void RedirectToMainMenu();

public:
    AccountSystem();
    virtual bool __VerifyUser(std::string fileName, std::string& user_account, std::string& pwd);

    virtual ~AccountSystem();
    void Logout();  // 通用功能，父类实现即可

    std::map<enum IdentifyType, std::string>& GetIdentifyMap2();
};


class EducationAccountSystem : public AccountSystem
{
protected:
    // 记录操作类
    //EduAppointmentRecordOperatorAb* pRecordOperator = nullptr;
};


class ManagerAccountSystem : public AccountSystem
{

private:
    bool __OpenFile(std::string filename, std::ios_base::openmode _Mode);

protected:
    // attr
    std::ifstream ifs;
    std::ofstream ofs;

    // 记录操作类
    ManagerRecordOperatorAb* pRecordOperator = nullptr;


    void OpenFile(std::string filename, std::ios_base::openmode _Mode)  throw (std::runtime_error);
    void CloseFile();

    bool writeFile(std::string filename, void* buf, std::streamsize size, std::ios_base::openmode _Mode);


    bool DisplayUserTypes();



    ManagerAccountSystem();
    ~ManagerAccountSystem();
    
};
