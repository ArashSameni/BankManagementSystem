#include "../headers/Loan.h"

int Loan::loansCount = 0;
QString Loan::fileName = "data/loans.json";

QJsonObject Loan::getLoan(int id)
{
	return getObject(Loan::fileName, QString::number(id));
}

void Loan::addLoan(Loan loan)
{
	QJsonObject loanObj;
	loanObj["id"] = loan.id;
	loanObj["fRequestAccount"] = loan.fRequestAccount;
	loanObj["fPaymentAccount"] = loan.fPaymentAccount;
	loanObj["fBankId"] = loan.fBankId;
	loanObj["amount"] = loan.amount;
	loanObj["status"] = loan.status;
	loanObj["countOfPayments"] = loan.countOfPayments;
	loanObj["lastTimePayed"] = loan.lastTimePayed;
	loanObj["requisitionDate"] = loan.requisitionDate;

	addObject(Loan::fileName, QString::number(loan.id), loanObj);
}

void Loan::removeLoan(int id)
{
	removeObject(Loan::fileName, QString::number(id));
}