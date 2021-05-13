#include "../../headers/structs/Bank.h"

int Bank::banksCount = 0;
QString Bank::fileName = "data/banks.json";

QJsonObject Bank::getBank(int id)
{
	return getObject(Bank::fileName, QString::number(id));
}

bool Bank::exists(int id)
{
	return existsObject(Bank::fileName, QString::number(id));
}

void Bank::addOrUpdateBank(Bank bank)
{
	QJsonObject bankObj;
	bankObj["id"] = bank.id;
	bankObj["name"] = toQString(bank.name);
	bankObj["totalBalance"] = bank.totalBalance;
	bankObj["foundationDate"] = bank.foundationDate;

	QJsonArray arr;
	for (int i = 0; i < bank.managers.size(); i++)
		arr.append(QJsonValue(toQString(bank.managers[i])));
	bankObj["managers"] = arr;

	QJsonArray arr1;
	for (int i = 0; i < bank.accounts.size(); i++)
		arr1.append(QJsonValue(bank.accounts[i]));
	bankObj["accounts"] = arr1;

	QJsonArray arr2;
	for (int i = 0; i < bank.loans.size(); i++)
		arr2.append(QJsonValue(bank.loans[i]));
	bankObj["loans"] = arr2;

	addOrUpdateObject(Bank::fileName, QString::number(bank.id), bankObj);
}

void Bank::removeBank(int id)
{
	removeObject(Bank::fileName, QString::number(id));
}

Bank Bank::getBankStruct(QJsonObject bankObj)
{
	Bank tempBank;
	tempBank.id = bankObj["id"].toInt();
	tempBank.name = bankObj["name"].toString().toStdString();
	tempBank.totalBalance = bankObj["totalBalance"].toInt();
	tempBank.foundationDate = bankObj["foundationDate"].toInt();

	QJsonArray arr = bankObj["managers"].toArray();
	foreach(QJsonValue x, arr)
		tempBank.managers.push_back(x.toString().toStdString());

	QJsonArray arr1 = bankObj["accounts"].toArray();
	foreach(QJsonValue x, arr1)
		tempBank.accounts.push_back(x.toInt());

	QJsonArray arr2 = bankObj["loans"].toArray();
	foreach(QJsonValue x, arr2)
		tempBank.loans.push_back(x.toInt());

	return tempBank;
}

Bank Bank::getBankStruct(int id)
{
	return getBankStruct(getBank(id));
}

std::vector<Bank> Bank::getAllBanks()
{
	std::vector<Bank> allBanks;
	QJsonObject obj = readFile(Bank::fileName).object();
	foreach(QJsonValue val, obj)
	{
		allBanks.push_back(Bank::getBankStruct(val.toObject()));
	}

	return allBanks;
}