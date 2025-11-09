#include "config.h"
Config::Config()
{
    ComputerRoomDetailFileName = "ComputerRoomDetail.csv";
    AppointRecordFileName = "appointment_record.csv";
    StudentAccountFileName = "Student.dat";
    TeacherAccountFileName = "Teacher.dat";
    AdminAccountFileName = "Admin.dat";
}

std::string Config::ComputerRoomDetailFileName = "ComputerRoomDetail.csv";
std::string Config::AppointRecordFileName = "appointment_record.csv";
std::string Config::StudentAccountFileName = "Student.dat";
std::string Config::TeacherAccountFileName = "Teacher.dat";
std::string Config::AdminAccountFileName = "Admin.dat";
