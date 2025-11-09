#include "account_system.h"

bool AccountSystem::__VerifyUser(std::string fileName, std::string& condicate_account, std::string& condicate_pwd)
{
    UserAccount user = {0};
    memset(&user, NULL, sizeof(user));
    std::ifstream ifs(fileName, std::ios::binary | std::ios::in);
    if(!ifs.is_open())
    {
        perror(std::string(fileName).append(": ").c_str());
        return false;
    }

    if(!ifs.read(reinterpret_cast<char*>(&user), sizeof(user)))
    {
        return false;
    }
    do {
        if((condicate_account.compare(user.accountId) == 0) && (condicate_pwd.compare(user.password) == 0))
        {
            this->mName = user.name;
            this->identify = this->IdentifyMap1.at(user.userType);
            this->mAccount = condicate_account;
            this->mPassword = condicate_pwd;
            return true;
        }
    } while(ifs.read(reinterpret_cast<char*>(&user), sizeof(user)));
    return false;
}

AccountSystem::AccountSystem() 
{
    isOnline = false;
    IdentifyMap1.insert(std::make_pair<int, IdentifyType>(1, Student));
    IdentifyMap1.insert(std::make_pair<int, IdentifyType>(2, Tearcher));
    IdentifyMap1.insert(std::make_pair<int, IdentifyType>(3, Admin));

    IdentifyMap2.insert(std::make_pair<IdentifyType, std::string>(Student, "学生"));
    IdentifyMap2.insert(std::make_pair<IdentifyType, std::string>(Tearcher, "教师"));
    IdentifyMap2.insert(std::make_pair<IdentifyType, std::string>(Admin, "管理员"));
}


bool AccountSystem::Login(int type)
{
    if(this->__Login())  // AccountSystem 为父类的 接口，回调到子类实现
    {   
        isOnline = true;
        identify = IdentifyMap1.at(type);
        
        // redirect  重定向到 登录成功的页面
        system("cls");
        std::cout << "登录成功，欢迎 [" << this->mName <<  IdentifyMap2.at(identify)  << "] 使用机房预约系统" << std::endl;
        this->DisplayAnyMenu();
    
        return true;
    }
    else
    {
        std::cout << "登录失败，账号或者密码错误，请重试" << std::endl;
        system("pause");

        return false;
    }
}

// 显示子菜单
void AccountSystem::DisplayAnyMenu()
{
    // 在这里检测状态
    // 1. 要在这里进行检测 登录状态
    // 状态通过可以进行后续的操作
    if(!this->CheckState())
    {
        std::cout << "登录失效，请重新登录..." << std::endl;

        this->RedirectToMainMenu();  // 重定向到 主菜单
    }
    // 一般是登录成功的，检测状态的代码可能多余的，暂时没遇到 重新登录的情况
    while(this->CheckState())
    {
        this->__DisplayAnyMenu();
        system("pause");
        system("cls");
    }
}

// 检测登录状态
bool AccountSystem::CheckState()
{
    return isOnline;
}

// 登录状态失效，重定向到主菜单
void AccountSystem::RedirectToMainMenu()
{
    std::cout << "重定向 RedirectToMainMenu" << std::endl;
    extern void SetupMainUi();
    SetupMainUi();  // 重定向到主菜单
}

// 清除登录信息
void AccountSystem::Logout() 
{
    isOnline = false;
    mAccount.clear();
    std::cout << "退出成功，即将跳转" << std::endl;
}

std::map<enum IdentifyType, std::string>& AccountSystem::GetIdentifyMap2()
{
    return IdentifyMap2;
}



AccountSystem::~AccountSystem() {}

ManagerAccountSystem::ManagerAccountSystem()
{
    pRecordOperator = new AdminAppointmentRecordOperator;
}

ManagerAccountSystem::~ManagerAccountSystem()
{
    if (pRecordOperator != nullptr)
        delete pRecordOperator;
}


bool ManagerAccountSystem::__OpenFile(std::string filename, std::ios_base::openmode _Mode)
{
    if(_Mode & std::ios_base::in)
    {
        ifs.open(filename, _Mode);
        return ifs.is_open();
    }
    if(_Mode & std::ios_base::out || _Mode & std::ios_base::app)
    {
        ofs.open(filename, _Mode);
        return ofs.is_open();
    }
    return false;
}

void ManagerAccountSystem::OpenFile(std::string filename, std::ios_base::openmode _Mode) throw (std::runtime_error)
{
    std::string msg = filename;
    if(!__OpenFile(filename, _Mode))
    {
        msg += ", Not Found";
        throw std::runtime_error(msg);
        
    }
}
void ManagerAccountSystem::CloseFile()
{
    LogUtils::LOGI(__func__);
    if(ifs.is_open())
        ifs.close();

    if(ofs.is_open())
    {
        ofs.flush();
        ofs.close();
    }
}
bool ManagerAccountSystem::writeFile(std::string filename, void* buf, std::streamsize size, std::ios_base::openmode _Mode)
{
    OpenFile(filename, _Mode);
    ofs.write(reinterpret_cast<const char*>(buf), size);
    CloseFile();
    return true;
}


bool ManagerAccountSystem::DisplayUserTypes()
{
    std::for_each(IdentifyMap2.begin(), IdentifyMap2.end(), 
        [](std::pair<const IdentifyType, std::string>& pair){
        std::cout << pair.first << ", " << pair.second << std::endl;
    });

    return false;
}