#include <iostream>
#include <QCoreApplication>
#include "headers/User.h"

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);
    Address::removeAddress(1);
    return 0;
}