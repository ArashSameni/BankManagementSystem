#include <QFile>
#include <QJsonDocument>

QJsonDocument readFile(QString fileName);
void writeFile(QString fileName, QJsonDocument& doc);