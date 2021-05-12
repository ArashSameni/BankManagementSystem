#include "../headers/file.h"

QJsonDocument readFile(QString fileName)
{
	fileName = fileName;
	QFile file(fileName);
	file.open(QIODevice::ReadOnly);
	QByteArray byteArray = file.readAll();
	file.close();
	return QJsonDocument::fromJson(byteArray);
}

void writeFile(QString fileName, QJsonDocument &doc)
{
	fileName = fileName;
	QFile file(fileName);
	file.open(QFile::WriteOnly | QFile::Truncate);
	file.write(doc.toJson());
	file.close();
}

bool fileExists(QString path)
{
	QFileInfo check_file(path);

	if (check_file.exists() && check_file.isFile())
		return true;
	else
		return false;
}

void createFileIfNotExist(QString path)
{
	if (!fileExists(path))
	{
		QFile file(path);
		file.open(QIODevice::WriteOnly);
		file.close();
	}
}