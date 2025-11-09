/*
    预约系统
*/
#include "schedule_system.h"


std::string ScheduleSystem::EqSym = std::string(30, '=');
std::string ScheduleSystem::_Sym1 = std::string(32, '-');
std::string ScheduleSystem::SpaceSym1 = std::string(30, ' ');
std::string ScheduleSystem::SpaceSym2 = std::string(10, ' ');


void ScheduleSystem::DisplayMenuHeader()
{
    std::cout << this->EqSym << " 欢迎来到机房预约系统 " << this->EqSym << std::endl << std::endl;
}