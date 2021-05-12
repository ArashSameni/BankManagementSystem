#include "../../headers/structs/Address.h"

int Address::addressesCount = 0;
QString Address::fileName = "data/addresses.json";

QJsonObject Address::getAddress(int id)
{
	return getObject(Address::fileName, QString::number(id));
}

void Address::addOrUpdateAddress(Address address)
{
	QJsonObject addressObj;
	addressObj["id"] = address.id;
	addressObj["country"] = toQString(address.country);
	addressObj["city"] = toQString(address.city);
	addressObj["street"] = toQString(address.street);
	addressObj["postalCode"] = address.postalCode;
	addressObj["plaqueNO"] = address.plaqueNO;

	addOrUpdateObject(Address::fileName, QString::number(address.id), addressObj);
}

void Address::removeAddress(int id)
{
	removeObject(Address::fileName, QString::number(id));
}

Address Address::getAddressStruct(QJsonObject addressObj)
{
	Address tempAddress;
	tempAddress.id = addressObj["id"].toInt();
	tempAddress.country = addressObj["country"].toString().toStdString();
	tempAddress.city = addressObj["city"].toString().toStdString();
	tempAddress.street = addressObj["street"].toString().toStdString();
	tempAddress.postalCode = addressObj["postalCode"].toInt();
	tempAddress.plaqueNO = addressObj["plaqueNO"].toInt();

	return tempAddress;
}

Address Address::getAddressStruct(int id)
{
	return getAddressStruct(getAddress(id));
}

std::vector<Address> Address::getAllAddresses()
{
	std::vector<Address> allAddresses;
	QJsonObject obj = readFile(Address::fileName).object();
	foreach(QJsonValue val, obj)
	{
		allAddresses.push_back(Address::getAddressStruct(val.toObject()));
	}

	return allAddresses;
}