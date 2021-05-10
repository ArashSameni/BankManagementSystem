#include <iostream>
#include <QJsonObject>
#include <QString>
#include "utilities.h"

struct Transition
{
    int id;
    static int transitionsCount;

    int sender;   // Foreign Key
    int receiver; // Foreign Key
    int amount;
    time_t transitionDate = time(0);
	
    static QString fileName;
    static QJsonObject getTransition(int id);
    static void addTransition(Transition transition);
    static void removeTransition(int id);
};

static Transition newTransition(int sender,
                                int receiver,
                                int amount)
{
    Transition tempTransition;
    tempTransition.id = ++Transition::transitionsCount;
    tempTransition.sender = sender;
    tempTransition.receiver = receiver;
    tempTransition.amount = amount;
    return tempTransition;
}