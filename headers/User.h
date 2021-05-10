#pragma once
#include <iostream>
#include <QJsonObject>
#include "Address.h"
#include "file.h"
#include "utilities.h"

struct User
{
	static int usersCount;

	int type = 1;            //1: NormalUser, 2: Bank Manager, 3: Full Admin
	std::string name;
	std::string username;    //This is primary key
	std::string password;
	std::string phoneNO;
	int addressId;		     //Foreign Key
	bool isBlocked = false;

	static bool exists(std::string username);
	static QJsonObject getUser(std::string username);
	static bool authenticate(std::string username, std::string password);
};

static User newUser(
	std::string username,
	std::string password,
	std::string name,
	int type = 1,
	std::string phoneNO = "",
	int addressId = 0)
{
	User tempUser;
	++User::usersCount;
	tempUser.type = type;
	tempUser.name = name;
	tempUser.username = username;
	tempUser.password = password;
	tempUser.phoneNO = phoneNO;
	tempUser.addressId = addressId;
	
	QJsonObject userObj;
	userObj["type"] = type;
	userObj["name"] = toQString(name);
	userObj["username"] = toQString(username);
	userObj["password"] = toQString(password);
	userObj["phoneNO"] = toQString(phoneNO);
	userObj["addressId"] = addressId;
	userObj["isBlocked"] = false;

	QJsonDocument doc = readFile("data/users.json");
	QJsonObject fileObj = doc.object();
	fileObj[toQString(username)] = userObj;
	doc.setObject(fileObj);
	writeFile("data/users.json", doc);
	return tempUser;
}
