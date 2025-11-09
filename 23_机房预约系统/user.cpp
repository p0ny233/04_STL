#include "user.h"

User::User()
{
    userTypeMap.insert(std::make_pair(0, Student));
    userTypeMap.insert(std::make_pair(1, Tearcher));
    userTypeMap.insert(std::make_pair(2, Admin));
}
