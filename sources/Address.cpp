#include "../headers/Address.h"

int Address::addressesCount = 0;
QString Address::fileName = "data/addresses.json";

QJsonObject Address::getAddress(int id)
{
	return getObject(Address::fileName, QString::number(id));
}

void Address::addAddress(Address address)
{
	QJsonObject addressObj;
	addressObj["id"] = address.id;
	addressObj["country"] = toQString(address.country);
	addressObj["city"] = toQString(address.city);
	addressObj["street"] = toQString(address.street);
	addressObj["postalCode"] = address.postalCode;
	addressObj["plaqueNO"] = address.plaqueNO;

	addObject(Address::fileName, QString::number(address.id), addressObj);
}

void Address::removeAddress(int id)
{
	removeObject(Address::fileName, QString::number(id));
}