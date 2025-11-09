#include "appointment_reord.h"


/////////////////////////////////  AppointmentRecordOperatorAbstract
// 1. 打开记录文件
bool AppointmentRecordOperatorAbstract::__OpenFile(std::string filename, std::ios_base::openmode _Mode)
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
    return true;
}

void AppointmentRecordOperatorAbstract::OpenFile(std::string filename, std::ios_base::openmode _Mode = std::ios_base::in)  // 默认是以读方式打开文件
{
    char buf[64] = {0};
    sprintf_s(buf, "%s, reason: ", filename.c_str());
    if(!__OpenFile(filename, _Mode))
    {
        perror(buf);
        exit(-1);
    }
}

// 2. 关闭文件
void AppointmentRecordOperatorAbstract::CloseFile()
{
    LogUtils::LOGI(__func__);

    if (ifs.is_open())
        ifs.close();
    
    if(ofs.is_open())
    {
        ofs.flush();
        ofs.close();
    }
    
}

////////////////////////////////////////// AppointmentRecordOperator
void AppointmentRecordOperator::__ReadAllLine(std::string cur_user_account, bool filter)
{
    int inFileRow = 1;
    int displayRow = 1;
    std::string line;
    displayRowRelatedInFileRowidx.clear();
    contents.clear();
    while(std::getline(this->ifs, line))
    {   
        contents.insert(std::make_pair(inFileRow++, line));
        if(filter)
        {
            if(line.find(cur_user_account) == std::string::npos )  // 找不到关键词
                continue;
            displayRowRelatedInFileRowidx.insert(std::make_pair(displayRow, inFileRow-1));
            displayRow++;
        }
        else
        {
            displayRowRelatedInFileRowidx.insert(std::make_pair(displayRow, inFileRow - 1));
            displayRow++;
        }
    }
}

// 排除 关键词 的行
bool AppointmentRecordOperator::ReadAllLineExcludeKeyWord(std::string keyword)
{
    OpenFile(Config::AppointRecordFileName);
    __ReadAllLineExcludeKeyWord(keyword);
    CloseFile();
    return true;
}

void AppointmentRecordOperator::__ReadAllLineExcludeKeyWord(std::string keyword)
{
    int inFileRow = 1;
    int displayRow = 1;
    std::string line;
    displayRowRelatedInFileRowidx.clear();
    contents.clear();
    while(std::getline(this->ifs, line))
    {   
        contents.insert(std::make_pair(inFileRow++, line));
        if (line.find(keyword) != std::string::npos)  // 找到关键词
            continue;
        displayRowRelatedInFileRowidx.insert(std::make_pair(displayRow, inFileRow - 1));
        displayRow++;
    }
}

void AppointmentRecordOperator::ReadAllLine(std::string cur_user_account, bool filter)
{
    OpenFile(Config::AppointRecordFileName);
    __ReadAllLine(cur_user_account, filter);
    CloseFile();
    
}

// 3. 显示内容
void AppointmentRecordOperator::DisplayContents()
{
    LogUtils::LOGI(__func__);
    std::for_each(displayRowRelatedInFileRowidx.begin(), displayRowRelatedInFileRowidx.end(), [&](std::pair<const int, int>& pair){
        std::cout << pair.first << "、" << this->contents.at(pair.second) << std::endl;
    });
}

void AppointmentRecordOperator::DisplayContentsForDisplay()
{
    LogUtils::LOGI(__func__);
    std::for_each(displayRowRelatedInFileRowidx.begin(), displayRowRelatedInFileRowidx.end(), [&](std::pair<const int, int>& pair){
        std::cout << pair.first << "、" << this->contents.at(pair.second);
    });
}

// 3. 添加记录
bool AppointmentRecordOperator::__AppendRecord(std::string line)
{
    LogUtils::LOGI(__func__);

    OpenFile(Config::AppointRecordFileName, std::ios_base::app);
    this->ofs << line << std::endl;
    this->ofs.flush();
    CloseFile();
    return true;
}

bool AppointmentRecordOperator::AddRecord(std::string line)
{
    LogUtils::LOGI(__func__);

    return __AppendRecord(line);
}

// 4. 修改记录
bool AppointmentRecordOperator::__ModifyRecord(int idx, std::string flag)  // idx 表示在文件中的具体行
{
    // 1. 先从 displayRowRelatedInFileRowidx 得到实际上文件中的行
    // 2. 再根据得到的行号，取出对应的行内容的对象
    LogUtils::LOGI(__func__);
    int infilepos = displayRowRelatedInFileRowidx.at(idx);
    int pos = this->contents.at(infilepos).rfind(",");
    std::string newLine(this->contents.at(infilepos).c_str(), pos+1);
    newLine += flag;
    this->contents.at(infilepos) = newLine;

    // 未写入文件
    __ReWriteFile();
    return true;
}

bool AppointmentRecordOperator::ModifyRecord(int idx, std::string flag)  // idx 表示在文件中的具体行
{
    return __ModifyRecord(idx, flag);
}


bool AppointmentRecordOperator::__ClearFileContent(std::string filename, std::ios_base::openmode _Mode)  // idx 表示在文件中的具体行
{
    this->OpenFile(filename, _Mode);
    this->CloseFile();
    return true;
}

bool AppointmentRecordOperator::__ReWriteFile()
{
    this->OpenFile(Config::AppointRecordFileName, std::ios_base::out);
    std::for_each(contents.begin(), contents.end(), [&](std::pair<const int, std::string>& pair){
        this->ofs << pair.second << std::endl;
        this->ofs.flush();
    });
    this->CloseFile();
    return true;
}

bool AppointmentRecordOperator::ClearFileContent(std::string filename, std::ios_base::openmode _Mode)
{
    return __ClearFileContent(filename, _Mode);
}

bool AppointmentRecordOperator::__DisplayCanCanCelItem()
{
    return ReadAllLineExcludeKeyWord("预约取消");
}

bool AppointmentRecordOperator::DisplayCanCanCelItem()
{
    bool ret = __DisplayCanCanCelItem();
    this->DisplayContents();
    return ret;

}


//////////////////////////////////////////  EduAppointmentRecordOperatorAb
EduAppointmentRecordOperatorAb::EduAppointmentRecordOperatorAb() : pAroa(new AppointmentRecordOperator) { }

// 1. 读取记录 将信息存入到map
void EduAppointmentRecordOperatorAb::__ReadAllRecord(std::string cur_user_account, bool filter)
{
    this->pAroa->ReadAllLine(cur_user_account, filter);

}

void EduAppointmentRecordOperatorAb::ViewAllAppointmentRecord(std::string cur_user_account, bool filter)
{
    this->__ReadAllRecord(cur_user_account, filter);
    this->pAroa->DisplayContents();
    
}

////////////////////////////////////////// StudentAppointmentRecordOperator
    // 1. 申请提交预约
void StudentAppointmentRecordOperator::__SubmitMyRecord(std::string line)
{
    this->pAroa->AddRecord(line);
}

void StudentAppointmentRecordOperator::SubmitMyRecord(std::string line)
{
    __SubmitMyRecord(line);
}

    // 2. 查看我的预约
void StudentAppointmentRecordOperator::ReadSelfRecord(std::string user_account, bool filter)
{
    __ReadAllRecord(user_account, filter);
}

// 3. 取消个人的预约 （需要映射表）
/*
    display pos -------> file pos        <int , int>
    file pos    -------> content line    <file pos, content line>
*/
bool StudentAppointmentRecordOperator::__CancelAppointmentRecord(int idx)
{
    return this->pAroa->ModifyRecord(idx, "预约取消");

}
bool StudentAppointmentRecordOperator::CancelAppointmentRecord(int idx)
{

    return __CancelAppointmentRecord(idx);

}

////////////////////////////////////////// Teacher
bool TeacherAppointmentRecordOperator::__AuditAppointmentRecord(int idx, std::string flag)
{
    return this->pAroa->ModifyRecord(idx, flag);
}
bool TeacherAppointmentRecordOperator::AuditAppointmentRecord(int idx, std::string flag)
{
    return __AuditAppointmentRecord(idx, flag);
    
}

bool TeacherAppointmentRecordOperator::__DisplayCanCanCelItem()
{
    return this->pAroa->DisplayCanCanCelItem();
}

bool TeacherAppointmentRecordOperator::DisplayCanCanCelItem()
{
    return __DisplayCanCanCelItem();
}


//////////////////////////////////////////  AdminAppointmentRecordOperator
AdminAppointmentRecordOperator::AdminAppointmentRecordOperator()
{
    this->pAroa = new AppointmentRecordOperator;
}

bool AdminAppointmentRecordOperator::ClearRecord(std::string filename)
{
    
    return this->pAroa->ClearFileContent(filename);
}





