#include "../headers/utilities.h"

QString toQString(std::string str)
{
	return QString::fromUtf8(str.c_str());
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