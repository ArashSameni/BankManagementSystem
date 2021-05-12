#include <QFile>
#include <QJsonDocument>
#include <QFileInfo>

QJsonDocument readFile(QString fileName);
void writeFile(QString fileName, QJsonDocument& doc);
bool fileExists(QString path);
void createFileIfNotExist(QString path);