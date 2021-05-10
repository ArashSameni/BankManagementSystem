#include "../headers/utilities.h"

QString toQString(std::string str)
{
	return QString::fromUtf8(str.c_str());
}

QJsonObject getObject(QString fileName, QString identifier)
{
	QJsonObject fileObj = readFile(fileName).object();
	if (fileObj.contains(identifier))
		return fileObj[identifier].toObject();
}

void addOrUpdateObject(QString fileName, QString identifier, QJsonObject obj)
{
	QJsonDocument doc = readFile(fileName);
	QJsonObject fileObj = doc.object();
	fileObj[identifier] = obj;
	doc.setObject(fileObj);
	writeFile(fileName, doc);
}

void removeObject(QString fileName, QString identifier)
{
	QJsonDocument doc = readFile(fileName);
	QJsonObject fileObj = doc.object();
	if (fileObj.contains(identifier))
	{
		fileObj.remove(identifier);
		doc.setObject(fileObj);
		writeFile(fileName, doc);
	}
}

bool existsObject(QString fileName, QString identifier)
{
	QJsonObject fileObj = readFile(fileName).object();
	return fileObj.contains(identifier);
}