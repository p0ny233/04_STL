#pragma once
#include <iostream>

class Player
{
    int mId;            // 选手编号
    std::string mName;  // 选手姓名
    double mScore;      // 选手成绩
public:
    Player(std::string name, int id);

    std::string GetName();

    int GetId();

    void SetScore(double score);
    double GetScore();


    ~Player();
};


struct WinnerInfo
{
    int mId;            // 选手编号
    char mName[64];     // 选手姓名
    double mScore;      // 选手成绩
};

struct WinAward
{
    WinnerInfo champion;          // 冠军
    WinnerInfo viceChampion;      // 亚军
    WinnerInfo bronzeMedalist;    // 季军
};
