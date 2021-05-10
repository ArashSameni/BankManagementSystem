#include <iostream>

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
    float interestRate = 0.1;
    bool isActive = true;
    time_t createDate = time(0);
    time_t lastInterestDate = time(0);
};
int BankAccount::accountsCount = 0;

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
        tempBankAccount.interestRate = 0.3;
        break;
    case 3:
        tempBankAccount.interestRate = 0.5;
        break;
    }
    tempBankAccount.balance = balance;

    return tempBankAccount;
}