#pragma once
#include <iostream>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <ctime>
#include "file.h"

QString toQString(std::string str);
QJsonObject getObject(QString fileName, QString identifier);
void addOrUpdateObject(QString fileName, QString identifier, QJsonObject obj);
void removeObject(QString fileName, QString identifier);
bool existsObject(QString fileName, QString identifier);
int countOfObjects(QString fileName);

int getMenuInput(int max);
std::string getStringInput(std::string inputName, bool required = true, bool withSpace = false);
int getIntInput(std::string inputName, bool required = true);

bool is_digits(const std::string& str);
std::string getDateTime(int unixTime, bool getTime = false);