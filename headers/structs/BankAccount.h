#pragma once
#include <iostream>
#include <QJsonObject>
#include <QString>
#include <vector>
#include "../utilities.h"
#include "../file.h"

struct BankAccount
{
    int id;
    static int accountsCount;

    std::string fUsername; // Foreign Key
    int fBankId;           // Foreign Key
    int balance = 0;
    int type = 1; // (1: short-term, 2: long-term, 3: special) account
    // 10% for short-term accounts
    // 30% for long-term accounts
    // 50% for special accounts
    float interestRate = 1.1;
    int status = 0;        // -1: Rejected 0:Pending 1:Accepted
    time_t createDate = time(0);
    time_t lastInterestDate = time(0);

    static QString fileName;
    static QJsonObject getAccount(int id);
    static void addOrUpdateAccount(BankAccount account);
    static void removeAccount(int id);
    static BankAccount getAccountStruct(QJsonObject accountObj);
    static BankAccount getAccountStruct(int id);
    static std::vector<BankAccount> getAllAccounts();
};

static BankAccount newBankAccount(std::string username,
                                  int bankId,
                                  int type = 1,
                                  int balance = 0)
{
    BankAccount tempBankAccount;
    tempBankAccount.id = ++BankAccount::accountsCount;
    tempBankAccount.fUsername = username;
    tempBankAccount.fBankId = bankId;
    tempBankAccount.type = type;
    switch (type)
    {
    case 2:
        tempBankAccount.interestRate = 1.3;
        break;
    case 3:
        tempBankAccount.interestRate = 1.5;
        break;
    }
    tempBankAccount.balance = balance;

    BankAccount::addOrUpdateAccount(tempBankAccount);
	
    return tempBankAccount;
}