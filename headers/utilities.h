#pragma once
#include <iostream>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include "file.h"

QString toQString(std::string str);
void removeObject(QString fileName, QString identifier);