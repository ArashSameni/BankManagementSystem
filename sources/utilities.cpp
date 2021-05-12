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

int countOfObjects(QString fileName)
{
	QJsonObject fileObj = readFile(fileName).object();
	return fileObj.keys().count();
}

std::string getStringInput(std::string inputName, bool required)
{
	std::string inp = "";
	if (!required)
		inputName += "(Enter to skip)";
	while (true)
	{
		std::cout << inputName << ": ";
		std::getline(std::cin, inp);
		if (!required || !inp.empty())
			break;
		else
			std::cout << inputName << " is required!" << std::endl;
	}
	return inp;
}

int getIntInput(std::string inputName, bool required)
{
	int res = 0;
	std::string inp = "";
	if (!required)
		inputName += "(Enter to skip)";
	while (true)
	{
		std::cout << inputName << ": ";
		std::getline(std::cin, inp);
		if (!inp.empty())
		{
			try
			{
				res = std::stoi(inp);
				break;
			}
			catch (...) 
			{
				std::cout << "Please enter valid " << inputName << std::endl;
			}
		}
		else if (!required)
			break;
		else
			std::cout << inputName << " is required!" << std::endl;
	}

	return res;
}