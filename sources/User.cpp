#include "../headers/User.h"

int User::usersCount = 0;

bool User::exists(std::string username)
{
	QJsonObject fileObj = readFile("data/users.json").object();
	return fileObj.contains(toQString(username));
}