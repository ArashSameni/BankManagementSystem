#pragma once
#include <iostream>
#include <QJsonObject>
#include <QString>
#include <vector>
#include <QJsonArray>
#include "../utilities.h"
#include "../file.h"

struct Bank
{
    int id;
    static int banksCount;

    std::string name;
    int totalBalance = 5000000;
    std::vector<std::string> managers;        // Foreign Key
    std::vector<int> accounts;
    std::vector<int> loans;
    time_t foundationDate = time(0);

    static QString fileName;
    static QJsonObject getBank(int id);
    static bool exists(int id);
    static void addOrUpdateBank(Bank bank);
    static void removeBank(int id);
    static Bank getBankStruct(QJsonObject bankObj);
    static Bank getBankStruct(int id);
    static std::vector<Bank> getAllBanks();
};

static Bank newBank(std::string name,
                    int totalBalance = 5000000)
{
    Bank tempBank;
    tempBank.id = ++Bank::banksCount;
    tempBank.name = name;
    tempBank.totalBalance = totalBalance;

    Bank::addOrUpdateBank(tempBank);
	
    return tempBank;
}