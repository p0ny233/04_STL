#include "competition_system.h"
#include <numeric>
#define _CRT_SECURE_NO_WARNINGS


// 重置 系统信息
void CompetitionSystem::ResetCSystem()
{
    ROUND = 1;
    this->players.clear();
    this->playerIds.clear();

    this->playerGroupIds1.clear();
    this->playerGroupIds2.clear();

    this->condicatePlayers.clear();
    this->condicatePlayersIds.clear();

    this->promotePlayers.clear();
    this->byGradeVector1.clear();
    this->byGradeVector2.clear();

    this->winPlayers.clear();
}


void CompetitionSystem::__StartGame(int number)
{
    
    int id = 10000;
    // 1. 创建比赛选手
    for(int i = 0; i < number; i++)
    {
        id = id + 1;
        playerIds.push_back(id);
        std::shared_ptr<Player> p(__CreatePlayer(std::string(1, 'A' + i), id));
        players.insert(std::make_pair<int&, std::shared_ptr<Player>&>(id, p));  // 模板参数类型乱写的？？没懂
    }

    condicatePlayers = players;

    std::cout << "如下是参赛各个选手信息: " << std::endl;
    this->__ShowPlayerInfo(condicatePlayers);

    // 2. 抽签

    condicatePlayersIds = playerIds;
    __GetDraw();
    __ShowDrawed();

    system("pause");
    
    // 3. 分组
    __GroupPlayer();

    // 4. 第一轮正式开始比赛
    __OfficalStartGameForRound();

    // 5. 第一轮比赛结束，显示成绩
    DisplayOrderByGrade();
    
    std::cout << "第" << ROUND << "轮比赛完毕" << std::endl;

    // 6. 显示晋级选手信息
    DisplayPromotePlayers();

    system("pause");

    // 7. 第二轮正式开始比赛
    system("cls");
    DisplayMenu();
    __ResetCondicatePlayerIds();
    std::cout << "第<< " << ROUND << " >>轮选手正在抽签"  << std::endl;
    __GetDraw();
    __ShowDrawed();
    __OfficalStartGameForRound();

    std::cout << "第" << ROUND << "轮比赛完毕" << std::endl;
    //system("pause");

    // 8. 显示晋级选手信息
    DisplayPromotePlayers();

    // 9. 保存比赛结果到文件
    SaveGameRecord();
}

// 第一轮比赛
void CompetitionSystem::__OfficalStartGameForRound()
{
    // 合并两个容器vector，合并的目的是想只用一次for_each就能给所有选手打分
    std::vector<int> lplayerIds;
    if(ROUND == 1)
    {
        lplayerIds.reserve(playerGroupIds1.size() + playerGroupIds2.size());
        std::copy(playerGroupIds1.begin(), playerGroupIds1.end(), std::back_inserter(lplayerIds));
        std::copy(playerGroupIds2.begin(), playerGroupIds2.end(), std::back_inserter(lplayerIds));
    }
    else if(ROUND == 2)
    {
        std::vector<int> vtmp;
        vtmp.reserve(promotePlayers.size());
        std::for_each(promotePlayers.begin(), promotePlayers.end(), [&](std::shared_ptr<Player>& p){ vtmp.push_back(p->GetId());});
        std::copy(vtmp.begin(), vtmp.end(), std::back_inserter(lplayerIds));
    }

    std::cout << "第 <<" << ROUND << ">> 轮比赛正式开始: " << std::endl;;
    srand(time(NULL));

    // 给每位选手打10次分数，然后去除其中最高分和最低分，最后求平均数，再按分数高到低 显示选手信息
    std::for_each(lplayerIds.begin(), lplayerIds.end(),
        [&](int val)
        {
            // 每位循环给打10次分数，然后去除其中最高分和最低分，最后记录平均
            // 创建容器记录 分数
            std::deque<double> scores;
            for(int i = 0; i < 10; i++)
            {
                scores.push_back(rand() % 100 * 1.0);

            }
            // 去除最高和最低分
            //std::for_each(scores.begin(), scores.end(), [](double val) {std::cout << val << " "; });
            //std::cout << std::endl;

            std::sort(scores.begin(), scores.end(), std::greater<double>());  // 从大到小

            //std::cout << std::endl;
            //std::for_each(scores.begin(), scores.end(), [](double val) {std::cout << val << " ";});
            
            scores.pop_front();  // 删除最高分
            scores.pop_back();   // 删除最低分

            //std::cout << std::endl;
            //std::for_each(scores.begin(), scores.end(), [](double val) {std::cout << val << " "; });
            // 计算平均值。
            double aver = std::accumulate(scores.begin(), scores.end(), 0) / scores.size();
            players[val]->SetScore(aver);
            //std::cout << "编号：" << players[val]->GetId()  
            //        << ", 姓名：" << players[val]->GetName() 
            //        << ", 成绩：" << players[val]->GetScore() << std::endl;
        });

        // 处理选手成绩
        ProcessOrderByGrade();
}

// 创建选手
Player* CompetitionSystem::__CreatePlayer(std::string name, int id)
{
    return new Player(name, id);

}

// 显式比赛选手Id
void CompetitionSystem::__ShowPlayerId(std::vector<int>& playerIds)
{
    std::for_each(playerIds.begin(), playerIds.end(), [](int  val) { std::cout << val << " "; });

}

// 显式比赛选手信息
void CompetitionSystem::__ShowPlayerInfo(std::map<int, std::shared_ptr<Player>>& players)
{
    std::for_each(players.begin(), players.end(), [](std::pair<const int, std::shared_ptr<Player>>& it) { 
                                          std::cout << "选手编号: " << it.first 
                                                    << ", 选手姓名: " << it.second->GetName() << std::endl; 
                                                });
}

// 对选手分组
void CompetitionSystem::__GroupPlayer()
{
    // 抽签后进行分组
    if(ROUND == 1)
    {
        playerGroupIds1.assign(condicatePlayersIds.begin(), condicatePlayersIds.begin() + 6);
        playerGroupIds2.assign(condicatePlayersIds.begin() + 6, condicatePlayersIds.end());
        std::cout << std::endl;
        std::cout << "第1小组比赛成员如下：" << std::endl;
        __ShowPlayerId(playerGroupIds1);

        std::cout << std::endl;

        std::cout << "第2小组比赛成员如下：" << std::endl;
        __ShowPlayerId(playerGroupIds2);
        std::cout << std::endl;

    }
    else if(ROUND == 2)
    {
        playerGroupIds1.assign(condicatePlayersIds.begin(), condicatePlayersIds.end());
        std::cout << "第1小组比赛成员如下：" << std::endl;
        __ShowPlayerId(playerGroupIds1);

    }
}

// 显式抽签后的结果
void CompetitionSystem::__ShowDrawed()
{
    std::cout << std::string(30, '-') << std::endl;
    std::cout << "抽签后演讲顺序如下: " << std::endl;
    //std::for_each(ids.begin(), ids.size(), [](int val) { std::cout << val << " "; });
    for(int i = 0; i < condicatePlayersIds.size(); i++)
    {
        std::cout << condicatePlayersIds.at(i) << " ";
    }
    std::cout << std::endl;
    std::cout << std::string(30, '-') << std::endl;

}

// 菜单显式
void CompetitionSystem::DisplayMenu()
{
    std::string sym1(50, '*');
    std::string sym2(15, '*');
    std::string op1 = "  欢迎参加演讲比赛  ";
    std::string op2 = "  1. 开始演讲比赛   ";
    std::string op3 = "  2. 查看往届记录   ";
    std::string op4 = "  3. 清空比赛记录   ";
    std::string op5 = "  4. 退出比赛程序   ";

    std::cout << sym1 << std::endl;

    std::cout << sym2 << op1 << sym2 << std::endl;
    std::cout << sym2 << op2 << sym2 << std::endl;
    std::cout << sym2 << op3 << sym2 << std::endl;
    std::cout << sym2 << op4 << sym2 << std::endl;
    std::cout << sym2 << op5 << sym2 << std::endl;

    std::cout << sym1 << std::endl;
}

// 开始比赛
void CompetitionSystem::StartGame(int number)
{
    this->ResetCSystem();
    __StartGame(number);
}

// 抽签
void CompetitionSystem::__GetDraw()
{
    srand(time(NULL));

    std::random_shuffle(this->condicatePlayersIds.begin(), this->condicatePlayersIds.end());
        
}

// 按成绩从高到低显示比赛选手信息
class OrderVec
{
public:
    bool operator()(std::shared_ptr<Player>& p1, std::shared_ptr<Player>& p2)
    {
        return p1->GetScore() > p2->GetScore();
    }
};
void CompetitionSystem::__DisplayPlayers(std::vector<std::shared_ptr<Player>>& target, int pos=0)
{
    std::vector<std::shared_ptr<Player>>::iterator itEnd;
    if(!pos)
        itEnd = target.end();
    else
    {
        itEnd = target.begin() + 3;
        winPlayers.assign(target.begin(), itEnd);  // 最终获奖者
    }
    
    
    std::for_each(target.begin(), itEnd, [](std::shared_ptr<Player>& p){

        std::cout << "编号: " << p->GetId()
                  << ", 姓名: " << p->GetName()
                  << ", 成绩: " << p->GetScore() 
                  << std::endl;});
}

// 显示比赛结果(按照成绩高到低)
void CompetitionSystem::DisplayOrderByGrade()
{

    std::cout << "第1小组比赛名次: " << std::endl;
    __DisplayPlayers(byGradeVector1);

    std::cout << "第2小组比赛名次: " << std::endl;
    __DisplayPlayers(byGradeVector2);

}

// 显示晋级选手
void CompetitionSystem::DisplayPromotePlayers()
{
    std::cout << "第" << ROUND << "轮晋级选手如下：" << std::endl;

    if(ROUND == 1)
    {
        __DisplayPlayers(promotePlayers);

    }
    else if(ROUND == 2)
    {
        __DisplayPlayers(promotePlayers, 3);

    }
    ROUND++;
}

// 重置 condicate中的选手id，第一轮是所有选手，第二轮是晋级选手
void CompetitionSystem::__ResetCondicatePlayerIds()
{
    condicatePlayersIds.clear();
    std::for_each(promotePlayers.begin(), promotePlayers.end(), [&](std::shared_ptr<Player>& p){ condicatePlayersIds.push_back(p->GetId());});
}

// 成绩高到低存储选手对象
void CompetitionSystem::ProcessOrderByGrade()
{
    if(ROUND == 1)
    {
        // 先把第1小组选手信息存到 byGradeVector，然后 OrderVec 内部根据 选手的成绩由高到低 对 byGradeVector排序
        std::for_each(playerGroupIds1.begin(), playerGroupIds1.end(), 
                [&](int v){
                    byGradeVector1.push_back((players[v]));
                });

        std::sort(byGradeVector1.begin(), byGradeVector1.end(), OrderVec());

        // 把第2小组选手信息存到 byGradeVector，然后 OrderVec 内部根据 选手的成绩由高到低 对 byGradeVector排序
        std::for_each(playerGroupIds2.begin(), playerGroupIds2.end(), 
                [&](int v){
                    byGradeVector2.push_back((players[v]));
                });

        std::sort(byGradeVector2.begin(), byGradeVector2.end(), OrderVec());

        for(int i = 0; i < 3; i++)
        {
            promotePlayers.push_back((byGradeVector1.at(i)));
        }
        for(int i = 0; i < 3; i++)
        {
            promotePlayers.push_back((byGradeVector2.at(i)));
        }
    }
    else if (ROUND == 2)
    {
        // 第二轮
        std::sort(promotePlayers.begin(), promotePlayers.end(), OrderVec());
    }

}

// 开始抽签
void CompetitionSystem::StartDrawed()
{
    __GetDraw();
}

// 保存比赛名次记录到文件
void CompetitionSystem::__SaveGameRecord()
{
    std::string fileName = "./speed.dat";
    // 1. 文件不存在，则创建
    std::ofstream ofs(fileName, std::ios::app | std::ios::binary);  // 以二进制方式打开文件
    // 2. 判断文件打开是否成功
    if(!ofs.is_open())
    {
        perror("打开文件失败");
        return;
    }
    // 冠军、亚军、季军 选手的信息结构体
    WinAward wad;
    memset(&wad, NULL, sizeof(wad));
    int i = 0;
    // 写入内容到文件
    std::for_each(winPlayers.begin(), winPlayers.end(), [&](std::shared_ptr<Player>& p){
                WinnerInfo wi;
                memset(&wi, NULL, sizeof(wi));

                wi.mId = p->GetId();

                int size = strlen(p->GetName().c_str());
                strcpy_s(wi.mName, size + 1, p->GetName().c_str());  // 第二个参数，需大于等于strlen(src)+1
                wi.mScore = p->GetScore();
                WinnerInfo* winfo = reinterpret_cast<WinnerInfo*>(&wad);
                memcpy(winfo + i, &wi, sizeof(WinnerInfo));
                i++;
    });

    ofs.write(reinterpret_cast<char*>(&wad), sizeof(WinAward));
    ofs.flush();
    ofs.close();
    std::cout << "结果保存成功" << std::endl;
}

// 保存比赛名次记录到文件
void CompetitionSystem::SaveGameRecord()
{
    __SaveGameRecord();
}

// 查看往届比赛名次记录
void CompetitionSystem::__ViewHistoryGameRecord()
{
    std::ifstream ifs("./speed.dat", std::ios::binary | std::ios::in);

    if(!ifs.is_open())
    {
        perror("打开文件失败");
        return;
    }
    WinAward wa;
    int i = 1;

    std::map<int, std::string> flags;
    flags.insert(std::make_pair<int, std::string>(0, "冠军"));
    flags.insert(std::make_pair<int, std::string>(1, "亚军"));
    flags.insert(std::make_pair<int, std::string>(2, "季军"));
    
    std::string sym(50, '-');
    //std::ifstream& is = dynamic_cast<std::ifstream&>();
    if(!ifs.read(reinterpret_cast<char*>(&wa), sizeof(wa)))
    {
        std::cout << "无比赛记录" << std::endl;
        return;
    }

    do {

        std::cout << std::endl;
        std::cout << "第" << i << "届" << std::endl;

        WinnerInfo info;
        WinnerInfo* pInfo = reinterpret_cast<WinnerInfo*>(&wa);
        for(int j = 0; j < 3; j++)
        {
            memset(&info, NULL, sizeof(info));
            memcpy(&info, pInfo + j, sizeof(info));
            std::cout << sym << std::endl;
            std::cout << flags[j]
                << "编号：" << info.mId
                << ", 姓名：" << info.mName
                << ", 成绩：" << info.mScore
                << std::endl;
        }
        std::cout << sym << std::endl;
        i++;
    } while(ifs.read(reinterpret_cast<char*>(&wa), sizeof(wa)));

    ifs.close();
}


// 查看往届比赛名次记录
void CompetitionSystem::ViewHistoryGameRecord()
{
    __ViewHistoryGameRecord();
}

// 清空比赛名次记录
void CompetitionSystem::ClearGameRecord()
{
    std::ofstream ofs("./speed.dat");
    
    if(!ofs.is_open())
    {
        perror("打开文件失败");
        return;
    }
    std::cout << "记录已被清除" << std::endl;
}


