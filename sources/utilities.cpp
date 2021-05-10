#include "../headers/utilities.h"

QString toQString(std::string str)
{
	return QString::fromUtf8(str.c_str());
}