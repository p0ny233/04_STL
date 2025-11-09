#include "computer_room_system.h"

ComputerRoomSystem::ComputerRoomSystem()
{
    Config c;
    char str[] = "机房编号: %d号机房,机房容量: %d人\n";
    std::error_code ec;
    std::string filename = Config::ComputerRoomDetailFileName;
    ofs.open(filename, std::ios_base::out);
    if (ofs.is_open() == false)
        std::cout << "文件打开失败" << std::endl;
    
    char buf[64];
    for(int i = 1; i <= 3; i++)
    {
        memset(buf, NULL, sizeof(buf));
        sprintf_s(buf, str, i, 50 * i);
        ofs.write(buf, strlen(buf) + 1);
    }
    ofs.flush();
    ofs.close();
}

bool ComputerRoomSystem::ViewComputerRoomDetail()
{
    ifs.open(Config::ComputerRoomDetailFileName, std::ios_base::in);
    if(ifs.is_open() == false)
        std::cout << "文件打开失败" << std::endl;

    std::string line;
    while(std::getline(this->ifs, line))
    {
        std::cout << line << std::endl;
    }
    ifs.close();
    return true;
}