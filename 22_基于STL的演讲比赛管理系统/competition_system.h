#pragma once
#include <vector>
#include <deque>  // 10个评委的分数，去除最高最低，头删尾删，因此选择 deque
#include <map>
#include <iostream>
#include <functional>
#include <algorithm>
#include <fstream>
#include "player.h"
/*
    比赛系统
*/
class CompetitionSystem
{
private:
    // attar
    int ROUND = 1;  // 第几轮比赛
    std::map<int, std::shared_ptr<Player>> players;  // 存储 <key(选手编号), value(shared_ptr指针)>
    std::vector<int> playerIds;                      // 存储 key(全部选手编号)
    std::vector<int> playerGroupIds1;                // 分组时，存储选手的编号
    std::vector<int> playerGroupIds2;                // 分组时，存储选手的编号
    
    // 进入比赛的选手以及id
    std::map<int, std::shared_ptr<Player>> condicatePlayers;
    std::vector<int> condicatePlayersIds;


    std::vector<std::shared_ptr<Player>> promotePlayers;  // 晋级的选手
    std::vector<std::shared_ptr<Player>> byGradeVector1;  // 按照Player成绩 降序存储
    std::vector<std::shared_ptr<Player>> byGradeVector2;  // 按照Player成绩 降序存储
    // 最终获奖者
    std::vector<std::shared_ptr<Player>> winPlayers;      // 最终获奖者
    

    int option;                      // 记录 菜单选择

    // method
    // 重置系统
    void ResetCSystem();

    // 开始比赛
    void __StartGame(int number);

    // 第一轮正式开始比赛
    void __OfficalStartGameForRound();

    // 抽签
    void __GetDraw();

    // 创建选手
    Player* __CreatePlayer(std::string name, int id);

    // 显式比赛选手信息
    void __ShowPlayerInfo(std::map<int, std::shared_ptr<Player>>& players);

    // 显式比赛选手Id
    void __ShowPlayerId(std::vector<int>& playerIds);

    // 显式抽签后的结果
    void __ShowDrawed();

    // 对选手分组
    void __GroupPlayer();

    // 显示选手信息
    void __DisplayPlayers(std::vector<std::shared_ptr<Player>>& target, int pos);

    // 成绩高到低存储选手对象
    void ProcessOrderByGrade();

    // 显示晋级选手
    void DisplayPromotePlayers();

    // 重置 condicate中的选手id，第一轮是所有选手，第二轮是晋级选手
    void __ResetCondicatePlayerIds();

    // 保存比赛名次记录到文件
    void __SaveGameRecord();

    void SaveGameRecord();

    // 查看往届比赛名次记录
    void __ViewHistoryGameRecord();


public:
    // 显式比赛菜单
    void DisplayMenu();

    // 开始比赛
    void StartGame(int);

    // 显示比赛结果(按照成绩高到低)
    void DisplayOrderByGrade();

    // 开始抽签
    void StartDrawed();  

    // 查看往届比赛名次记录
    void ViewHistoryGameRecord();

    // 清空比赛名次记录
    void ClearGameRecord();

    ~CompetitionSystem()
    {
        // 将每个选手的内存清理掉
        //std::for_each();
        players.clear();
        std::cout << "欢迎下次使用" << std::endl;

    }
};