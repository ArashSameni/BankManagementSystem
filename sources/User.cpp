#include "../headers/User.h"

int User::usersCount = 0;
QString User::fileName = "data/users.json";

bool User::exists(std::string username)
{
	return existsObject(User::fileName, toQString(username));
}

QJsonObject User::getUser(std::string username)
{
	return getObject(User::fileName, toQString(username));
}

void User::addUser(User user)
{
	QJsonObject userObj;
	userObj["type"] = user.type;
	userObj["name"] = toQString(user.name);
	userObj["username"] = toQString(user.username);
	userObj["password"] = toQString(user.password);
	userObj["phoneNO"] = toQString(user.phoneNO);
	userObj["addressId"] = user.addressId;
	userObj["isBlocked"] = false;

	addObject(User::fileName, toQString(user.username), userObj);
}


void User::removeUser(std::string username)
{
	removeObject(User::fileName, toQString(username));
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