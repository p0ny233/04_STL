#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include "config.h"
#include "utils.h"

/*
    一条记录有如下元素:
        1. 发起申请预约的时间
        2. 申请人姓名
        3. 学号
        4. 要预约的时间 (周几)
        5. 要预约的时间段 (上午、下午)
        6. 机房编号
        7. 预约的状态 (审核中、预约成功、预约失败、取消预约)
    
*/

enum AppointmentRecordState
{
    UnderReview, Confirmed, Faild, Cancel
};

//////////////////////////////////////////////////////////////////////////////////////////////////
// 预约记录操作抽象类 (共性)
class AppointmentRecordOperatorAbstract
{

private:
    bool __OpenFile(std::string filename, std::ios_base::openmode _Mode);

protected:
    // attr
    std::ifstream ifs;
    std::ofstream ofs;
    std::map<int, std::string> contents;               // <line number, line>
    std::map<int, int> displayRowRelatedInFileRowidx;  // <display, infile>

    // methods 
     // 打开记录文件
    void OpenFile(std::string filename, std::ios_base::openmode _Mode);
    // 关闭记录文件
    void CloseFile();


public:
    virtual void ReadAllLine(std::string cur_user_account, bool filter) = 0;
    virtual void DisplayContents() = 0;
    virtual bool AddRecord(std::string) = 0;
    virtual bool ModifyRecord(int idx, std::string flag) = 0;
    virtual bool ClearFileContent(std::string, std::ios_base::openmode = std::ios_base::out) = 0;

    // 显示可取消的项(可以被取消才显示)
    virtual bool DisplayCanCanCelItem() = 0;
};

class AppointmentRecordOperator : public AppointmentRecordOperatorAbstract
{
private:
    bool __AppendRecord(std::string);
    void __ReadAllLine(std::string cur_user_account, bool filter);
    void __ReadAllLineExcludeKeyWord(std::string keyword);
    bool __ModifyRecord(int idx, std::string flag);
    bool __ClearFileContent(std::string, std::ios_base::openmode = std::ios_base::out);
    bool __ReWriteFile();

    bool __DisplayCanCanCelItem();

public:
    virtual void ReadAllLine(std::string cur_user_account, bool filter);
    virtual void DisplayContents();
    void DisplayContentsForDisplay();
    virtual bool AddRecord(std::string);
    virtual bool ModifyRecord(int idx, std::string);
    bool ClearFileContent(std::string, std::ios_base::openmode=std::ios_base::out);
    bool ReadAllLineExcludeKeyWord(std::string keyword="");

    bool DisplayCanCanCelItem();

};


/////////////////////////////  学生和教师的基类
class EduAppointmentRecordOperatorAb
{

protected:
    AppointmentRecordOperatorAbstract* pAroa;

public:
    EduAppointmentRecordOperatorAb();

    // 1. 读取所有预约记录
    void __ReadAllRecord(std::string cur_user_account="", bool filter = false);

    // 2. 查看所有预约
    void ViewAllAppointmentRecord(std::string cur_user_account = "", bool filter = false);

    // 1. 申请提交预约 (接口，学生端实现)
    virtual void SubmitMyRecord(std::string line) = 0;

    // 2. 取消预约
    virtual bool CancelAppointmentRecord(int idx) = 0;

    // 3. 显示可以被审核的预约记录
    virtual bool DisplayCanCanCelItem() = 0;
    virtual bool AuditAppointmentRecord(int, std::string) = 0;
};

//////////////////////////// 学生类
class StudentAppointmentRecordOperator : public EduAppointmentRecordOperatorAb 
{
private:
    // 教师端接口，高耦合
    bool DisplayCanCanCelItem() { return false;}
    bool AuditAppointmentRecord(int, std::string) { return false;}

    // 1. 申请提交预约
    void __SubmitMyRecord(std::string line);

    // 3. 取消预约
    bool __CancelAppointmentRecord(int idx);

public:

    // 1. 申请提交预约
    void SubmitMyRecord(std::string line);

    // 2. 查看我的预约
    void ReadSelfRecord(std::string, bool filter = false);

    // 3. 取消预约
    bool CancelAppointmentRecord(int idx);
};

////////////////////////////  教师
class TeacherAppointmentRecordOperator : public EduAppointmentRecordOperatorAb  // 要实现 EduAppointmentRecordOperatorAb 所有接口
{
private:

    // 学生端的接口，高耦合了，不符合开发原则
    void SubmitMyRecord(std::string line) {};
    bool CancelAppointmentRecord(int) { return false;};

    bool __AuditAppointmentRecord(int, std::string flag);

protected:
    bool __DisplayCanCanCelItem();
    


public:

    // 1. 查看所有人预约 【父类实现，指针类型是父类，调用时，直接调用父类的】
    //void ViewAllAppointmentRecord(std::string);

    // 2.1 显示可以被审核的预约记录
    bool DisplayCanCanCelItem();
    // 2. 审核所有人预约
    bool AuditAppointmentRecord(int, std::string flag);
};

////////// 管理员
class ManagerRecordOperatorAb
{

protected:
    AppointmentRecordOperatorAbstract* pAroa;  // 组合关系

public:
    virtual bool ClearRecord(std::string) = 0;
};

class AdminAppointmentRecordOperator : public ManagerRecordOperatorAb
{

public:
    AdminAppointmentRecordOperator();

    bool ClearRecord(std::string);

};
