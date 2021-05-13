#include "../../headers/structs/User.h"

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
	userObj["username"] = toQString(user.username).toLower();
	userObj["password"] = toQString(user.password);
	userObj["phoneNO"] = toQString(user.phoneNO);
	userObj["addressId"] = user.addressId;
	userObj["isBlocked"] = false;
	userObj["bankId"] = user.bankId;

	QJsonArray arr1;
	for (int i = 0; i < user.accounts.size(); i++)
		arr1.append(QJsonValue(user.accounts[i]));
	userObj["accounts"] = arr1;

	QJsonArray arr2;
	for (int i = 0; i < user.loans.size(); i++)
		arr2.append(QJsonValue(user.loans[i]));
	userObj["loans"] = arr2;
	
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
	tempUser.isBlocked = userObj["isBlocked"].toBool();
	tempUser.bankId = userObj["bankId"].toInt();
	
	QJsonArray arr1 = userObj["accounts"].toArray();
	foreach(QJsonValue x, arr1)
		tempUser.accounts.push_back(x.toInt());
	
	QJsonArray arr2 = userObj["loans"].toArray();
	foreach(QJsonValue x, arr2)
		tempUser.loans.push_back(x.toInt());
	return tempUser;
}

User User::getUserStruct(std::string username)
{
	return getUserStruct(getUser(username));
}

std::vector<User> User::getAllUsers()
{
	std::vector<User> allUsers;
	QJsonObject obj = readFile(User::fileName).object();
	foreach(QJsonValue val, obj)
	{
		allUsers.push_back(User::getUserStruct(val.toObject()));
	}

	return allUsers;
}