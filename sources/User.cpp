#include "../headers/User.h"

int User::usersCount = 0;
QString User::fileName = "data/users.json";

bool User::exists(std::string username)
{
	QJsonObject fileObj = readFile(User::fileName).object();
	return fileObj.contains(toQString(username));
}

QJsonObject User::getUser(std::string username)
{
	QJsonObject fileObj = readFile(User::fileName).object();
	if (fileObj.contains(toQString(username)))
		return fileObj[toQString(username)].toObject();
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

	QJsonDocument doc = readFile(User::fileName);
	QJsonObject fileObj = doc.object();
	fileObj[toQString(user.username)] = userObj;
	doc.setObject(fileObj);
	writeFile(User::fileName, doc);
}

void User::removeUser(std::string username)
{
	QString QUserName = toQString(username);
	QJsonDocument doc = readFile(User::fileName);
	QJsonObject fileObj = doc.object();
	if (fileObj.contains(QUserName))
	{
		fileObj.remove(QUserName);
		doc.setObject(fileObj);
		writeFile(User::fileName, doc);
	}
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