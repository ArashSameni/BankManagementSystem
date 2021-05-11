#include "../../headers/structs/Bank.h"

int Bank::banksCount = 0;
QString Bank::fileName = "data/banks.json";

QJsonObject Bank::getBank(int id)
{
	return getObject(Bank::fileName, QString::number(id));
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

	QJsonArray arr = bankObj["postalCode"].toArray();
	foreach(QJsonValue x, arr)
		tempBank.managers.push_back(x.toString().toStdString());
	return tempBank;
}

Bank Bank::getBankStruct(int id)
{
	return getBankStruct(getBank(id));
}