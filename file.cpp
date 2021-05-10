#include "headers/file.h"

QJsonDocument readFile(QString fileName)
{
	QFile file(fileName);
	file.open(QIODevice::ReadOnly);
	QByteArray byteArray = file.readAll();
	file.close();
	return QJsonDocument::fromJson(byteArray);
}


void writeFile(QString fileName, QJsonDocument& doc)
{
	QFile file(fileName);
	file.open(QFile::WriteOnly | QFile::Truncate);
	file.write(doc.toJson());
	file.close();
}