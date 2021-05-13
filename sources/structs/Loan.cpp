#include "../../headers/structs/Loan.h"

int Loan::loansCount = 0;
QString Loan::fileName = "data/loans.json";

QJsonObject Loan::getLoan(int id)
{
	return getObject(Loan::fileName, QString::number(id));
}

bool Loan::exists(int id)
{
	return existsObject(Loan::fileName, QString::number(id));
}

void Loan::addOrUpdateLoan(Loan loan)
{
	QJsonObject loanObj;
	loanObj["id"] = loan.id;
	loanObj["fRequestAccount"] = loan.fRequestAccount;
	loanObj["fPaymentAccount"] = loan.fPaymentAccount;
	loanObj["fBankId"] = loan.fBankId;
	loanObj["amount"] = loan.amount;
	loanObj["status"] = loan.status;
	loanObj["countOfPayments"] = loan.countOfPayments;
	loanObj["countOfPaid"] = loan.countOfPaid;
	loanObj["isFinished"] = loan.isFinished;
	loanObj["lastTimePayed"] = loan.lastTimePayed;
	loanObj["requisitionDate"] = loan.requisitionDate;

	addOrUpdateObject(Loan::fileName, QString::number(loan.id), loanObj);
}

void Loan::removeLoan(int id)
{
	removeObject(Loan::fileName, QString::number(id));
}

Loan Loan::getLoanStruct(QJsonObject loanObj)
{
	Loan tempLoan;
	tempLoan.id = loanObj["id"].toInt();
	tempLoan.fRequestAccount = loanObj["fRequestAccount"].toInt();
	tempLoan.fPaymentAccount = loanObj["fPaymentAccount"].toInt();
	tempLoan.fBankId = loanObj["fBankId"].toInt();
	tempLoan.amount = loanObj["amount"].toInt();
	tempLoan.status = loanObj["status"].toInt();
	tempLoan.countOfPayments = loanObj["countOfPayments"].toInt();
	tempLoan.countOfPaid = loanObj["countOfPaid"].toInt();
	tempLoan.isFinished = loanObj["isFinished"].toBool();
	tempLoan.lastTimePayed = loanObj["lastTimePayed"].toInt();
	tempLoan.requisitionDate = loanObj["requisitionDate"].toInt();

	return tempLoan;
}

Loan Loan::getLoanStruct(int id)
{
	return getLoanStruct(getLoan(id));
}

std::vector<Loan> Loan::getAllLoans()
{
	std::vector<Loan> allLoans;
	QJsonObject obj = readFile(Loan::fileName).object();
	foreach(QJsonValue val, obj)
	{
		allLoans.push_back(Loan::getLoanStruct(val.toObject()));
	}

	return allLoans;
}