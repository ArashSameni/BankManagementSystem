#include "../headers/Bank.h"

int Bank::banksCount = 0;
QString Bank::fileName = "data/banks.json";

QJsonObject getBank(int id)
{
	return getObject(Bank::fileName, QString::number(id));
}

void addBank(Bank bank)
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

	addObject(Bank::fileName, QString::number(bank.id), bankObj);
}

void removeBank(int id)
{
	removeObject(Bank::fileName, QString::number(id));
}