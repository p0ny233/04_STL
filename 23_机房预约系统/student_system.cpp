/*
    学生端
*/
#include "student_system.h"

// 校验账号密码
bool StudentSideSystem::VerifyUser(std::string& user_account, std::string& pwd)
{
    return this->__VerifyUser(Config::StudentAccountFileName, user_account, pwd);
}

// 显示登录后的菜单
bool StudentSideSystem::__DisplayAnyMenu()
{   
    std::cout << "1. 申请预约" << std::endl;
    std::cout << "2. 查看我的预约" << std::endl;
    std::cout << "3. 查看所有预约" << std::endl;
    std::cout << "4. 取消预约" << std::endl;
    std::cout << "5. 注销登录" << std::endl;
    int op;
    std::cin >> op;
    switch(op)
    {
        case 1:
            AppointmentApplication();
            break;
        case 2:
            ViewMyAppointment();
            break;
        case 3:
            ViewALLPointment();
            break;
        case 4:
            CancelAppointment();
            break;
        case 5:
            this->Logout();
            break;
    }
    return true;
}

// 构造
StudentSideSystem::StudentSideSystem()
{
    this->pRecordOperator = new StudentAppointmentRecordOperator;
}

// 0. 登录
bool StudentSideSystem::__Login()
{
    std::string stuNo;
    std::string pwd;
    std::cout << "请输入学号: " << std::endl;
    std::cin >> stuNo;
    std::cout << "请输入密码: " << std::endl;
    std::cin >> pwd;

    // 校验账号密码是否正确
    return this->VerifyUser(stuNo, pwd);
    
}
void StudentSideSystem::Login(int type)
{
    this->AccountSystem::Login(type);
}

/*

class AppointmentRecord
{
    char currenTime[64];   // 提交预约记录的时间
    char name[64];         // 申请人姓名
    char no[20];           // 学号
    char week[20];         // 预约的时间 (周几)
    char timePeriod[20];   // 预约的时间段 (上午、下午)
    char CRNumber[10];     // 机房编号
    enum AppointmentRecordState state;            // 预约状态
};


*/
// 1. 申请预约 私有接口
bool StudentSideSystem::__AppointmentApplication()
{
    bool isSuccess;

    int op1;
    //AppointmentRecord* acord = new AppointmentRecord;
    std::string record1;
    std::string record2;
    std::map<int, std::string> weekens;
    weekens.insert(std::make_pair<int, std::string>(1, "周一"));
    weekens.insert(std::make_pair<int, std::string>(2, "周二"));
    weekens.insert(std::make_pair<int, std::string>(3, "周三"));
    weekens.insert(std::make_pair<int, std::string>(4, "周四"));
    weekens.insert(std::make_pair<int, std::string>(5, "周五"));
    std::for_each(weekens.begin(), weekens.end(), [](std::pair< const int, std::string>& pair) {
        std::cout << pair.first << "、" << pair.second << std::endl;;
        });
    std::cout << "请输入申请的时间: " << std::endl;
    std::cin >> op1;
    record2.append(this->mName).append(",");     // 姓名
    record2.append(this->mAccount).append(",");  // id
    record2.append(weekens[op1]).append(",");  // 预约的时间


    std::map<int, std::string> timePeriods;
    timePeriods.insert(std::make_pair<int, std::string>(1, "上午"));
    timePeriods.insert(std::make_pair<int, std::string>(2, "下午"));
    std::for_each(timePeriods.begin(), timePeriods.end(), [](std::pair< const int, std::string>& pair) {
        std::cout << pair.first << "、" << pair.second << std::endl;;
        });
    std::cout << "请输入申请的时间段: " << std::endl;
    std::cin >> op1;
    record2.append(timePeriods[op1]).append(",");  // 预约的时间段

    std::map<int, std::string> CRType;  // 机房
    CRType.insert(std::make_pair<int, std::string>(1, "1号机房 — 最大容量30人"));
    CRType.insert(std::make_pair<int, std::string>(2, "2号机房 — 最大容量50人"));
    CRType.insert(std::make_pair<int, std::string>(3, "3号机房 — 最大容量100人"));
    std::for_each(CRType.begin(), CRType.end(), [](std::pair< const int, std::string>& pair) {
        std::cout << pair.first << "、" << pair.second << std::endl;;
        });
    std::cout << "请输入申请的机房类型: " << std::endl;
    std::cin >> op1;
    record2.append(CRType[op1]).append(",");  // 预约的时间

    // 预约状态
    std::map< enum AppointmentRecordState, std::string> RecordState;
    RecordState.insert(std::make_pair<enum AppointmentRecordState, std::string>(UnderReview, "审核中"));
    RecordState.insert(std::make_pair<enum AppointmentRecordState, std::string>(Confirmed, "预约成功"));
    RecordState.insert(std::make_pair<enum AppointmentRecordState, std::string>(Faild, "预约失败"));
    RecordState.insert(std::make_pair<enum AppointmentRecordState, std::string>(Cancel, "取消的预约"));
    enum AppointmentRecordState state = UnderReview;
    record2.append(RecordState[state]);  // 预约的状态
    record1 = getCurrentTime();
    record1.append(",").append(record2);

    std::cout << record1 << std::endl;
    // 将记录写入
    this->pRecordOperator->SubmitMyRecord(record1);
    system("pause");
    isSuccess = true;
    return isSuccess;
}

// 1. 申请预约
void StudentSideSystem::AppointmentApplication()
{
    bool ret = __AppointmentApplication();
    if (ret)
        std::cout << "提交成功" << std::endl;
    else
        std::cout << "提交失败" << std::endl;
}

// 2. 查看我的预约   私有接口  bool __ViewMyAppointment
bool StudentSideSystem::__ViewMyAppointment()
{
    this->pRecordOperator->ViewAllAppointmentRecord(this->mAccount, true);
    return true;
}
// 2. 查看我的预约
void StudentSideSystem::ViewMyAppointment()
{
    bool ret = __ViewMyAppointment();
    if(ret)
        std::cout << "查询完成" << std::endl;
    else
        std::cout << "查询失败" << std::endl;
}

// 3. 查看所有预约
void StudentSideSystem::ViewALLPointment()
{
    this->pRecordOperator->ViewAllAppointmentRecord();
}
// 4. 取消预约
bool StudentSideSystem::__CancelAppointment(int idx)
{
    return this->pRecordOperator->CancelAppointmentRecord(idx);
}

void StudentSideSystem::CancelAppointment()
{
    int op;
    // 1. 先显示当前账户的记录
    ViewMyAppointment();
    std::cout << "请输入要取消预约的编号: " << std::endl;
    std::cin >> op;
    
    bool ret = __CancelAppointment(op);
    if(ret)
        std::cout << "操作完成" << std::endl;
    else
        std::cout << "操作失败" << std::endl;
}