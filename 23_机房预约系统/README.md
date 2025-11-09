## QA

### 2025/11/08

接口类

```cpp
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
    //virtual bool DisplayCanCanCelItem() = 0;
    //virtual void AuditAppointmentRecord() = 0;
};
```

实现类

```cpp
class StudentAppointmentRecordOperator : public EduAppointmentRecordOperatorAb 
{
    ...
    ...
    ...
};

class TeacherAppointmentRecordOperator : public EduAppointmentRecordOperatorAb
{
    ...
    ...
    ...
};
```

`StudentAppointmentRecordOperator` 和 `TeacherAppointmentRecordOperator` 两个类都继承同个接口，
因此两个类都要同时实现相同接口，高耦合，扩展性差

`StudentAppointmentRecordOperator` 和 `TeacherAppointmentRecordOperator` 接口相互冗余

目前将错就错，先把功能全部实现，后期优化一版，解耦合





