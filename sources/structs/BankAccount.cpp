#include "../../headers/structs/BankAccount.h"

int BankAccount::accountsCount = 0;
QString BankAccount::fileName = "data/accounts.json";

QJsonObject BankAccount::getAccount(int id)
{
	return getObject(BankAccount::fileName, QString::number(id));
}

bool BankAccount::exists(int id)
{
	return existsObject(BankAccount::fileName, QString::number(id));
}

void BankAccount::addOrUpdateAccount(BankAccount account)
{
	QJsonObject accountObj;
	accountObj["id"] = account.id;
	accountObj["fUsername"] = toQString(account.fUsername);
	accountObj["fBankId"] = account.fBankId;
	accountObj["balance"] = account.balance;
	accountObj["type"] = account.type;
	accountObj["interestRate"] = account.interestRate;
	accountObj["status"] = account.status;
	accountObj["createDate"] = account.createDate;
	accountObj["lastInterestDate"] = account.lastInterestDate;
	
	addOrUpdateObject(BankAccount::fileName, QString::number(account.id), accountObj);
}

void BankAccount::removeAccount(int id)
{
	removeObject(BankAccount::fileName, QString::number(id));
}

BankAccount BankAccount::getAccountStruct(QJsonObject accountObj)
{
	BankAccount tempAccount;
	tempAccount.id = accountObj["id"].toInt();
	tempAccount.fUsername = accountObj["fUsername"].toString().toStdString();
	tempAccount.fBankId = accountObj["fBankId"].toInt();
	tempAccount.balance = accountObj["balance"].toInt();
	tempAccount.type = accountObj["type"].toInt();
	tempAccount.interestRate = accountObj["interestRate"].toDouble();
	tempAccount.status = accountObj["status"].toInt();
	tempAccount.createDate = accountObj["createDate"].toInt();
	tempAccount.lastInterestDate = accountObj["lastInterestDate"].toInt();
	
	return tempAccount;
}

BankAccount BankAccount::getAccountStruct(int id)
{
	return getAccountStruct(getAccount(id));
}

std::vector<BankAccount> BankAccount::getAllAccounts()
{
	std::vector<BankAccount> allAccounts;
	QJsonObject obj = readFile(BankAccount::fileName).object();
	foreach(QJsonValue val, obj)
	{
		allAccounts.push_back(BankAccount::getAccountStruct(val.toObject()));
	}

	return allAccounts;
}