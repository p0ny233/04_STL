#pragma once
#include <iostream>
#include <map>
enum IdentifyType
{
    Student=1, Tearcher, Admin
};

enum AuditOptionType
{
    PASS, REJECT
};

typedef enum AuditOptionType AuditOptionTypes;

struct UserAccount
{

    int userType;
    char name[64];
    char accountId[32];
    char password[32];
    
};


class User
{
protected:
    std::map<int, enum IdentifyType> userTypeMap;
    std::string mName;      // 姓名
    std::string mAccount;   // 账号
    std::string mPassword;  // 密码
    int mType;              // 用户类型 (学生、教师、管理员)

public:
    User();
};
