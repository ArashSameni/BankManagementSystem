#include <iostream>
#include "Address.h"

struct User
{
    static int usersCount;

    int type = 1; //1: NormalUser, 2: Bank Manager, 3: Full Admin
    std::string name;
    std::string username; //This is primary key
    std::string password;
    std::string phoneNO;
    Address address;
    bool isBlocked = false;
};
int User::usersCount = 0;

static User newUser(std::string name,
                    std::string username,
                    std::string password,
                    int type = 1,
                    std::string phoneNO = "",
                    Address address = newAddress())
{
    User tempUser;
    ++User::usersCount;
    tempUser.type = type;
    tempUser.name = name;
    tempUser.username = username;
    tempUser.password= password;
    tempUser.phoneNO = phoneNO;
    tempUser.address = address;
    return tempUser;
}