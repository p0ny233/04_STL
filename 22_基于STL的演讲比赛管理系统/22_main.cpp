#include "competition_system.h"

int main(void)
{
    CompetitionSystem* cs = new CompetitionSystem();
    bool run = true;
    while(run)
    {
        system("cls");
        cs->DisplayMenu();
        int option;
        std::cout << "请选择: ";
        std::cin >> option;
        //option = 1;
        switch(option)
        {
            case 1:  // 开始演讲比赛
                cs->StartGame(12);  // 指定12位比赛选手参赛
                break;
            case 2:  // 查看往届记录
                cs->ViewHistoryGameRecord();
                break;
            case 3:  // 清空比赛记录
                cs->ClearGameRecord();
                break;
            case 4:
                delete cs;
                cs = nullptr;
                run = false;
        }
        system("pause");

    }
    if(cs != nullptr)
        delete cs;
    return 0;
}
