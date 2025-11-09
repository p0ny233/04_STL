#include "teacher_system.h"

bool TeacherSideSystem::__DisplayAnyMenu()
{
    std::cout << "1. 查看所有预约" << std::endl;
    std::cout << "2. 审核预约" << std::endl;
    std::cout << "3. 注销登录" << std::endl;

    int op;
    std::cin >> op;
    switch(op)
    {
    case 1:
        ViewAllAppointment();
        break;
    case 2:
        ReviewAppointment();
        break;
    case 3:
        this->Logout();
        break;
    }

    return true;
}

// 0. 登录
bool TeacherSideSystem::__Login()
{    
    std::string TeaNo;
    std::string pwd;
    std::cout << "请输入职工号: " << std::endl;
    std::cin >> TeaNo;
    std::cout << "请输入密码: " << std::endl;
    std::cin >> pwd;

    // 校验账号密码是否正确
    return this->__VerifyUser(Config::TeacherAccountFileName, TeaNo, pwd);
    
}
TeacherSideSystem::TeacherSideSystem()
{
    pRecordOperator = new TeacherAppointmentRecordOperator;
    // TODO 无法自行推导!!!
    //optionMap.insert(std::make_pair<AuditOptionTypes, const char(&)[7]>(PASS, "通过"));
    //optionMap.insert(std::make_pair<AuditOptionTypes, const char(&)[10]>(REJECT, "未通过"));


    optionMap.insert(std::make_pair(PASS, "通过"));
    optionMap.insert(std::make_pair(REJECT, "未通过"));
}


void TeacherSideSystem::Login(int type)
{
    this->AccountSystem::Login(type);

}

// 1. 查看所有预约
void TeacherSideSystem::ViewAllAppointment()
{
    this->pRecordOperator->ViewAllAppointmentRecord();
}
// 2. 显示可以被审核预约记录
bool TeacherSideSystem::DisplayCanCanCelItem()
{
    return this->pRecordOperator->DisplayCanCanCelItem();
}
void TeacherSideSystem::ReviewAppointment()
{
    // 先显示可以被审核的预约，然后根据序号进行记录修改
    bool ret = DisplayCanCanCelItem();
    if(ret)
    {
        LogUtils::LOGI("查询完成");

    }
    else
    {
        LogUtils::LOGI("查询失败");
        return;
    }
    int op1;
    int op2;
    std::cout << "请输入审核项的序号: ";
    std::cin >> op1;
    std::cout << "请输入该项是否审核通过: " << std::endl;
    std::for_each(optionMap.begin(), optionMap.end(), [](std::pair<const AuditOptionTypes, std::string>& pair){
        std::cout << pair.first << "、" << pair.second << std::endl;
    });
    std::cin >> op2;
    this->pRecordOperator->AuditAppointmentRecord(op1, optionMap.at(AuditOptionTypes(op2)));
}