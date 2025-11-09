#include "player.h"

Player::Player(std::string name, int id) : mName(name), mId(id), mScore(0.0)
{
    //std::cout << this->mName << ", Player 构造函数" << std::endl;
}

std::string Player::GetName()
{
    return this->mName;
}

int Player::GetId()
{
    return this->mId;
}

void Player::SetScore(double score)
{
    this->mScore = score;
}

double Player::GetScore()
{
    return this->mScore;
}

Player::~Player()
{
    //std::cout << this->mName << ", Player 析构函数" << std::endl;
}
