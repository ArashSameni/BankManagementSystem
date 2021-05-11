#pragma once
#include <iostream>
#include <QJsonObject>
#include "Address.h"
#include "../utilities.h"

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

	static QString fileName;
	static bool exists(std::string username);
	static QJsonObject getUser(std::string username);
	static void addOrUpdateUser(User user);
	static bool authenticate(std::string username, std::string password);
	static void removeUser(std::string username);
	static User getUserStruct(QJsonObject userObj);
	static User getUserStruct(std::string username);
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

	User::addOrUpdateUser(tempUser);
	
	return tempUser;
}