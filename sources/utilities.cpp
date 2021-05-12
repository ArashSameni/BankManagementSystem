#include "../headers/utilities.h"
#include "../headers/UI/colors.h"

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
	int max = 0;
	QStringList keys = readFile(fileName).object().keys();
	foreach(QString num, keys)
	{
		int key = num.toInt();
		if (key > max)
			max = key;
	}
	return max;
}

int getMenuInput(int max)
{
	int res = 0;
	std::string inp = "";
	while (true)
	{
		std::cout << cyan << "  Input: " << reset;
		std::getline(std::cin, inp);
		if (inp == "-1")
			return -1;
		else if (!inp.empty())
		{
			try
			{
				res = std::stoi(inp);
				if (res < 1 || res > max)
					std::cout << red << "    " << "Wrong input!" << reset << std::endl << std::endl;
				else
					break;
			}
			catch (...)
			{
				std::cout << red << "    " << "Wrong input!" << reset << std::endl << std::endl;
			}
		}
		else
			std::cout << red << "    " << "Wrong input!" << reset << std::endl << std::endl;
	}
	return res;
}

std::string getStringInput(std::string inputName, bool required, bool withSpace)
{
	std::string inp = "";
	if (!required)
		inputName += "(Enter to skip)";
	while (true)
	{
		std::cout << cyan << "  " << inputName << ": " << reset;
		std::getline(std::cin, inp);
		if (inp == "-1")
			return inp;
		else if(!withSpace && inp.find(" ") != std::string::npos)
			std::cout << red << "    invalid " << inputName << "!" << reset << std::endl;
		else if (!required || !inp.empty())
			break;
		else
			std::cout << red << "    " << inputName << " is required!" << reset << std::endl;
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
		std::cout << cyan << "  " << inputName << ": " << reset;
		std::getline(std::cin, inp);
		if (inp == "-1")
			return -1;
		else if (!inp.empty())
		{
			try
			{
				res = std::stoi(inp);
				break;
			}
			catch (...)
			{
				std::cout << red << "    " << "Please enter valid " << inputName << reset << std::endl;
			}
		}
		else if (!required)
			break;
		else
			std::cout << red << "    " << inputName << " is required!" << reset << std::endl;
	}

	return res;
}

bool is_digits(const std::string& str)
{
	return str.find_first_not_of("0123456789") == std::string::npos;
}

std::string getDateTime(int unixTime, bool getTime)
{
	using std::to_string;
	time_t unix_time = unixTime;
	tm* ltm = localtime(&unix_time);
	std::string dateTime = to_string(ltm->tm_year + 1900) + "-" + to_string(ltm->tm_mon + 1) + "-" + to_string(ltm->tm_mday);

	if (getTime)
		dateTime += " " + to_string(ltm->tm_hour + 1) + ":" + to_string(ltm->tm_min) + ":" + to_string(ltm->tm_sec);

	return dateTime;
}