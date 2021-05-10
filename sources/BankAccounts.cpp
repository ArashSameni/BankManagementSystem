#include "../headers/BankAccount.h"

int BankAccount::accountsCount = 0;
QString BankAccount::fileName = "data/accounts.json";

QJsonObject BankAccount::getAccount(int id)
{
	return getObject(BankAccount::fileName, QString::number(id));
}

void BankAccount::addAccount(BankAccount account)
{
	QJsonObject accountObj;
	accountObj["id"] = account.id;
	accountObj["fUsername"] = toQString(account.fUsername);
	accountObj["fBankId"] = account.fBankId;
	accountObj["balance"] = account.balance;
	accountObj["type"] = account.type;
	accountObj["interestRate"] = account.interestRate;
	accountObj["isActive"] = account.isActive;
	accountObj["createDate"] = account.createDate;
	accountObj["lastInterestDate"] = account.lastInterestDate;
	
	addObject(BankAccount::fileName, QString::number(account.id), accountObj);
}

void BankAccount::removeAccount(int id)
{
	removeObject(BankAccount::fileName, QString::number(id));
}