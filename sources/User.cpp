#include "../headers/User.h"

int User::usersCount = 0;

bool User::exists(std::string username)
{
	QJsonObject fileObj = readFile("data/users.json").object();
	return fileObj.contains(toQString(username));
}

QJsonObject User::getUser(std::string username)
{
	QJsonObject fileObj = readFile("data/users.json").object();
	if (fileObj.contains(toQString(username)))
		return fileObj[toQString(username)].toObject();
}

bool User::authenticate(std::string username, std::string password)
{
	if (exists(username))
	{
		QJsonObject userObj = getUser(username);
		return userObj["password"].toString() == toQString(password);
	}

	return false;
}