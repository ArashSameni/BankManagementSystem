#pragma once
#include <iostream>
#include <QJsonObject>
#include <vector>
#include "../utilities.h"
#include "../file.h"

struct Loan
{
    int id;
    static int loansCount;

    int fRequestAccount;     // Foreign Key
    int fPaymentAccount;    // Foreign Key
    int fBankId;           // Foreign Key
    int amount;
    int status = 0;       // 0: Pending, -1: Rejected, 1: Accepted, 2: Finished, -2:  Blocked
    int countOfPayments;
    int countOfPaid = 0;
    bool isFinished = false;
    time_t lastTimePayed = 0;
    time_t requisitionDate = time(0);

    static QString fileName;
    static QJsonObject getLoan(int id);
    static void addOrUpdateLoan(Loan loan);
    static void removeLoan(int id);
    static Loan getLoanStruct(QJsonObject loanObj);
    static Loan getLoanStruct(int id);
    static std::vector<Loan> getAllLoans();
    static bool exists(int id);
};

static Loan newLoan(int requestAccount,
                    int bankId,
                    int amount,
					int countOfPayments,
                    int paymentAccount = 0)
{
    Loan tempLoan;
    tempLoan.id = ++Loan::loansCount;
    tempLoan.fRequestAccount = requestAccount;
    tempLoan.fPaymentAccount = requestAccount;
    if(paymentAccount)
        tempLoan.fPaymentAccount = paymentAccount;
    tempLoan.fBankId = bankId;
    tempLoan.amount = amount;
    tempLoan.countOfPayments = countOfPayments;

    Loan::addOrUpdateLoan(tempLoan);
	
    return tempLoan;
}