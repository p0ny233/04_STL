#include "computer_room_schedule_system.h"

ComputerRoomScheduleSystem::ComputerRoomScheduleSystem()
{
    this->pAdministractionSystem = new AdministrationSideSystem();
    this->pStudentSystem = new StudentSideSystem();
    this->pTeacherSystem = new TeacherSideSystem();
}

void ComputerRoomScheduleSystem::DisplayMainMenu()
{
    std::cout << "请选择要登陆的身份: " << std::endl;
    std::cout << this->SpaceSym1 << this->_Sym1 << std::endl;
    std::cout << this->SpaceSym1 << "|" << this->SpaceSym2 << this->SpaceSym2 << this->SpaceSym2 << "|" << std::endl;
    std::cout << this->SpaceSym1 << "|" << this->SpaceSym2 << "1.学生代表" << this->SpaceSym2 << "|" << std::endl;
    std::cout << this->SpaceSym1 << "|" << this->SpaceSym2 << this->SpaceSym2 << this->SpaceSym2 << "|" << std::endl;
    std::cout << this->SpaceSym1 << "|" << this->SpaceSym2 << "2.老    师" << this->SpaceSym2 << "|" << std::endl;
    std::cout << this->SpaceSym1 << "|" << this->SpaceSym2 << this->SpaceSym2 << this->SpaceSym2 << "|" << std::endl;
    std::cout << this->SpaceSym1 << "|" << this->SpaceSym2 << "3.管 理 员" << this->SpaceSym2 << "|" << std::endl;
    std::cout << this->SpaceSym1 << "|" << this->SpaceSym2 << this->SpaceSym2 << this->SpaceSym2 << "|" << std::endl;
    std::cout << this->SpaceSym1 << "|" << this->SpaceSym2 << "0.退    出" << this->SpaceSym2 << "|" << std::endl;
    std::cout << this->SpaceSym1 << "|" << this->SpaceSym2 << this->SpaceSym2 << this->SpaceSym2 << "|" << std::endl;
    std::cout << this->SpaceSym1 << this->_Sym1 << std::endl;
}

// 子菜单(学生、老师、管理员) 进行登录
void ComputerRoomScheduleSystem::StudentLogin()
{
    this->pStudentSystem->Login(Student);
}


void ComputerRoomScheduleSystem::TeacherLogin()
{
    this->pTeacherSystem->Login(Tearcher);
}


void ComputerRoomScheduleSystem::AdminLogin()
{
    this->pAdministractionSystem->Login(Admin);
}