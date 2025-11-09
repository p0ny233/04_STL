#pragma once
#include <string>
#include <fstream>
#include "config.h"


class ComputerRoomSystem
{

    std::ifstream ifs;
    std::ofstream ofs;

public:

    ComputerRoomSystem();

    bool ViewComputerRoomDetail();
};

