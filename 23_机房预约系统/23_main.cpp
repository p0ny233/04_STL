#include <iostream>
#include "computer_room_schedule_system.h"

ComputerRoomScheduleSystem* const crs = new ComputerRoomScheduleSystem;
// TODO：可以设计成 单例模式

void SetupMainUi()
{
    while(true)
    {
        system("cls");
        int input;
        crs->DisplayMainMenu();
        std::cout << "请输入你的选择: " << std::endl;

        std::cin >> input;
        switch(input)
        {
        case 0:
            std::cout << "欢迎下次使用" << std::endl;
            if (crs != nullptr)
                delete crs;
            return;
        case 1:
            crs->StudentLogin();
            break;
        case 2:
            crs->TeacherLogin();
            break;
        case 3:
            crs->AdminLogin();
            break;
        }
    }
}

int main(void)
{
    SetupMainUi();
    return 0;
}