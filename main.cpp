#include <iostream>
#include <QCoreApplication>
#include "headers/User.h"

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

	std::cout << User::authenticate("aras", "12354");
    return 0;
}