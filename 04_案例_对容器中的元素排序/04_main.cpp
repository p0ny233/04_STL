#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

class Player;

bool myCompare(double d1, double d2)
{
    return d1 > d2;
}

void printDeque(std::deque<double>& d)
{
    // iterator         普通迭代器
    // reverse_iterator 反转迭代器
    // const_iterator   只读迭代器
    for(std::deque<double>::const_iterator it = d.begin(); it != d.end(); it++)
    {

        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

class Player
{
public:
    std::string mName;
    Player(std::string name)
    {
        mName = name;
        std::cout << this->mName <<  " Player 构造函数" << ",this: " << this << std::endl;
    }

    // 拷贝构造
    Player(const Player& ref)
    {
        this->mName = ref.mName;
        std::cout << this->mName << " Player 拷贝函数" << ",this: " << this << std::endl;

    }

    ~Player()
    {
        std::cout << this->mName << " ~Player 析构函数" << ",this: " << this << std::endl;
    }
    std::deque<double> mScores;
    double mAverage;


};

void printAverage(const Player& player)
{
    std::cout << player.mName << " " << player.mAverage << std::endl;
}


void test01()
{
    Player A = Player("A");
    Player B = Player("B");
    Player C = Player("C");
    Player D = Player("D");
    Player E = Player("E");

    std::vector<Player> players;
    players.reserve(5);    // 注释掉这行，会发现输出很多的构造和析构函数
    players.push_back(A);  // players 一开始没有预留空间，那么会一边push_back一边扩容，一边重复调用 Player拷贝构造函数，扩容成本高
    players.push_back(B);
    players.push_back(C);
    players.push_back(D);
    players.push_back(E);
    srand(time(NULL));

    for(std::vector<Player>::iterator it = players.begin(); it < players.end(); it++)
    {
        for(int i = 0;  i < 10; i++)
        {
            int j = 0;
            while (!j--);
            int num = rand();
            (*it).mScores.push_back(num);
        }
    }

    for(std::vector<Player>::iterator it = players.begin(); it < players.end(); it++)
    {

        // 排序 从大到小
        sort((*it).mScores.begin(), (*it).mScores.end(), myCompare);
        // 去除最高和最低分
        std::deque<double>& ref = (*it).mScores;
        printDeque((*it).mScores);

        ref.pop_front();
        ref.pop_back();
        printDeque((*it).mScores);

        // 累加算平均分
        double total = 0;
        for(int i = 0; i < ref.size(); i++)
        {
            total += ref.at(i);
        }
        (*it).mAverage = total / ref.size();

        printAverage((*it));
    }
}

int main(void)
{
    test01();
    return 0;
}