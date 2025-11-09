#include "admin_system.h"

bool AdministrationSideSystem::__DisplayAnyMenu()
{
    std::cout << "1. 添加账号" << std::endl;
    std::cout << "2. 查看账号" << std::endl;
    std::cout << "3. 查看机房" << std::endl;
    std::cout << "4. 清空预约" << std::endl;
    std::cout << "5. 清空学生账户" << std::endl;
    std::cout << "6. 清空老师账户" << std::endl;
    std::cout << "7. 注销登录" << std::endl;

    int op;
    std::cin >> op;
    switch(op)
    {
    case 1:
        AddUserFor();
        break;
    case 2:
        ViewUsers();
        break;
    case 3:
        ViewComputerRoomDetail();
        break;
    case 4:
        ClearAppointment();
        break;
    case 5:
        ClearStudentAccount();
        break;
    case 6:
        ClearTeacherAccount();
        break;
    case 7:
        this->Logout();
        break;
    }
    return true;

}

AdministrationSideSystem::AdministrationSideSystem()
{
    pComputerRoomSystem = new ComputerRoomSystem;
}

AdministrationSideSystem::~AdministrationSideSystem()
{
    if(pComputerRoomSystem != nullptr)
        delete pComputerRoomSystem;
}

void AdministrationSideSystem::Login(int type)
{
    this->AccountSystem::Login(type);
    
}

bool AdministrationSideSystem::__Login()
{
    std::string condicate_account;
    std::string condicate_pwd;

    std::cout << "请输入管理员账号: " << std::endl;
    std::cin >> condicate_account;

    std::cout << "请输入管理员密码: " << std::endl;
    std::cin >> condicate_pwd;
        
    if(condicate_account.compare("root") == 0 && condicate_pwd.compare("root") == 0)
    {
        this->mName = "root";
        this->identify = Admin;
        this->mAccount = condicate_account;
        return true;
    }

    
    return this->__VerifyUser(Config::AdminAccountFileName, condicate_account, condicate_pwd);
}

// 1. 添加账号(学生还是老师)
bool AdministrationSideSystem::__AddUserFor()
{
    UserAccount user;

    std::cout << "选择添加账户类型：" << std::endl;
    std::map<int, enum IdentifyType> userTypeMap;
    userTypeMap.insert(std::make_pair(1, Student));
    userTypeMap.insert(std::make_pair(2, Tearcher));
    
    std::for_each(userTypeMap.begin(), userTypeMap.end(), [&](std::pair<const int, enum IdentifyType>& pair) {
        std::cout << pair.first << "、" << this->GetIdentifyMap2().at(pair.second) << std::endl;
        });
    int op;
    std::cin >> op;

    // 账户类型
    enum IdentifyType accountType = userTypeMap.at(op);
    user.userType = accountType;
    std::string userfileName;
    if(userTypeMap.at(op) == Student)
    {
        // 学号
        std::string no;
        std::cout << "请输入学号: " << std::endl;
        std::cin >> no;
        memcpy(user.accountId, no.c_str(), no.length()+1);
        userfileName = Config::StudentAccountFileName;
    }
    else if(userTypeMap.at(op) == Tearcher)
    {
        // 职工号
        std::string no;
        std::cout << "请输入职工号: " << std::endl;
        std::cin >> no;
        memcpy(user.accountId, no.c_str(), no.length() + 1);
        userfileName = Config::TeacherAccountFileName;
    }
    else
    {
        userfileName = Config::AdminAccountFileName;
    }
    // 姓名
    std::string name;
    std::cout << "请输入姓名: " << std::endl;
    std::cin >> name;
    memcpy(user.name, name.c_str(), name.length() + 1);

    // 密码
    std::string password;
    std::cout << "请输入密码: " << std::endl;
    std::cin >> password;
    memcpy(user.password, password.c_str(), password.length() + 1);
    return writeFile(userfileName, &user, sizeof(user), std::ios_base::app | std::ios_base::binary);
}



void AdministrationSideSystem::AddUserFor()
{
    bool ret = __AddUserFor();
    if(ret)
        std::cout << "用户添加成功" << std::endl;
    else
        std::cout << "用户添加失败" << std::endl;
        
}

bool AdministrationSideSystem::__ViewUsers(int op)
{
    std::string filename;
    if(Student == IdentifyMap1.at(op))
    {
        filename = Config::StudentAccountFileName;
    }
    else if(Tearcher == IdentifyMap1.at(op))
    {
        filename = Config::TeacherAccountFileName;
    }
    else
    {
        return false;
    }

    try 
    {
        UserAccount user;

        OpenFile(filename, std::ios_base::in | std::ios_base::binary);
        memset(&user, NULL, sizeof(user));
        while(ifs.read(reinterpret_cast<char*>(&user), sizeof(user)))
        {

            std::cout << "用户类型: " << IdentifyMap2.at(IdentifyMap1.at(user.userType))
                << ", 用户id: " << user.accountId
                << ", 用户名: " << user.name
                << ", 用户密码: " << user.password << std::endl;

        }

    }
    catch(std::runtime_error& e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }

    CloseFile();
}

bool AdministrationSideSystem::__ClearStudentAccount()
{
    OpenFile(Config::StudentAccountFileName, std::ios_base::out);
    CloseFile();
    return true;
}

bool AdministrationSideSystem::__ClearTeacherAccount()
{
    OpenFile(Config::TeacherAccountFileName, std::ios_base::out);
    CloseFile();
    return true;
}

void AdministrationSideSystem::ClearStudentAccount()
{
    bool ret = __ClearStudentAccount();
    if (ret)
        std::cout << "操作完成" << std::endl;
}

void AdministrationSideSystem::ClearTeacherAccount()
{
    bool ret = __ClearTeacherAccount();

    if(ret)
        std::cout << "操作完成" << std::endl;
}





// 2. 查看账号(学生还是老师)
void AdministrationSideSystem::ViewUsers()
{
    LogUtils::LOGI(__func__);
    // core logic
    int op;
    // 1. 确定查看学生还是老师
    DisplayUserTypes();
    std::cin >> op;
    bool ret = __ViewUsers(op);
    if(ret)
        std::cout << "查询完成" << std::endl;
    else
        std::cout << "查询失败" << std::endl;
}

// 3. 查看机房(显示机房编号以及最大容量
bool AdministrationSideSystem::__ViewComputerRoomDetail()
{
    

    return true;
}

void AdministrationSideSystem::ViewComputerRoomDetail()
{
    bool ret = false;
    try
    {
        ret = pComputerRoomSystem->ViewComputerRoomDetail();
    }
    catch(std::runtime_error& e)
    {
        std::cout << e.what() << std::endl;
    }

    if(ret)
        std::cout << "查询完成" << std::endl;
    else

        std::cout << "查询失败" << std::endl;
}

// 4. 清空预约
void AdministrationSideSystem::ClearAppointment()
{
    bool ret = this->pRecordOperator->ClearRecord(Config::AppointRecordFileName);
    if(ret)
    {
        std::cout << "记录已清空" << std::endl;
    }
    else
    {
        std::cout << "记录清空失败" << std::endl;
        
    }
    
}
