#include <iostream>
#include <QCoreApplication>
#include "headers/User.h"

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);
	if(!User::exists("arash2"))
	{
		User arash = newUser("arash2", "1234", "arasham be mola");
	}
    return a.exec();
}