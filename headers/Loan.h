#include <iostream>

struct Loan
{
    int id;
    static int loansCount;

    int fRequestAccount;     // Foreign Key
    int fPaymentAccount;    // Foreign Key
    int fBankId;           // Foreign Key
    int amount;
    int status = 0;       // 0: Pending, -1: Rejected, 1: Accepted
    int countOfPayments = 0;
    time_t lastTimePayed;
    time_t requisitionDate = time(0);
};
int Loan::loansCount = 0;

static Loan newLoan(int requestAccount,
                    int bankId,
                    int amount,
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
    return tempLoan;
}