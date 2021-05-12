#pragma once
#include <iostream>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include "file.h"

QString toQString(std::string str);
QJsonObject getObject(QString fileName, QString identifier);
void addOrUpdateObject(QString fileName, QString identifier, QJsonObject obj);
void removeObject(QString fileName, QString identifier);
bool existsObject(QString fileName, QString identifier);
int countOfObjects(QString fileName);

std::string getStringInput(std::string inputName, bool required = true);
int getIntInput(std::string inputName, bool required = true);