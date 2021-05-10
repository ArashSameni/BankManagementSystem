#include <iostream>
#include <vector>

struct Bank
{
    int id;
    static int banksCount;

    std::string name;
    int totalBalance = 5000000;
    std::vector<std::string> managers;         // Foreign Key
    time_t foundationDate = time(0);
};
int Bank::banksCount = 0;

static Bank newBank(std::string name,
                    int totalBalance = 5000000)
{
    Bank tempBank;
    tempBank.id = ++Bank::banksCount;
    tempBank.name = name;
    tempBank.totalBalance = totalBalance;
    return tempBank;
}