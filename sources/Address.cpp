#include "../headers/Address.h"

int Address::addressesCount = 0;
QString Address::fileName = "data/addresses.json";

QJsonObject Address::getAddress(int id)
{
	QString QsId = QString::number(id);
	QJsonObject fileObj = readFile(Address::fileName).object();
	if (fileObj.contains(QsId))
		return fileObj[QsId].toObject();
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

	QJsonDocument doc = readFile(Address::fileName);
	QJsonObject fileObj = doc.object();
	fileObj[QString::number(address.id)] = addressObj;
	doc.setObject(fileObj);
	writeFile(Address::fileName, doc);
}

void Address::removeAddress(int id)
{
	removeObject(Address::fileName, QString::number(id));
}