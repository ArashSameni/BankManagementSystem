#include "../../headers/structs/User.h"

int User::usersCount = 0;
QString User::fileName = "data/users.json";

bool User::exists(std::string username)
{
	return existsObject(User::fileName, toQString(username).toLower());
}

QJsonObject User::getUser(std::string username)
{
	return getObject(User::fileName, toQString(username).toLower());
}

void User::addOrUpdateUser(User user)
{
	QJsonObject userObj;
	userObj["type"] = user.type;
	userObj["name"] = toQString(user.name);
	userObj["username"] = toQString(user.username);
	userObj["password"] = toQString(user.password);
	userObj["phoneNO"] = toQString(user.phoneNO);
	userObj["addressId"] = user.addressId;
	userObj["isBlocked"] = false;

	addOrUpdateObject(User::fileName, toQString(user.username).toLower(), userObj);
}


void User::removeUser(std::string username)
{
	removeObject(User::fileName, toQString(username).toLower());
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

User User::getUserStruct(QJsonObject userObj)
{
	User tempUser;
	tempUser.type = userObj["type"].toInt();
	tempUser.name = userObj["name"].toString().toStdString();
	tempUser.username = userObj["username"].toString().toStdString();
	tempUser.password = userObj["password"].toString().toStdString();
	tempUser.phoneNO = userObj["phoneNO"].toString().toStdString();
	tempUser.addressId = userObj["addressId"].toInt();
	tempUser.isBlocked = userObj["type"].toBool();
	
	return tempUser;
}

User User::getUserStruct(std::string username)
{
	return getUserStruct(getUser(username));
}