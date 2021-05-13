#pragma once
#include <iostream>
#include <QJsonObject>
#include <QString>
#include <vector>
#include "../utilities.h"
#include "BankAccount.h"
#include "../file.h"

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
    static void addOrUpdateTransition(Transition transition);
    static void removeTransition(int id);
    static Transition getTransitionStruct(QJsonObject transitionObj);
    static Transition getTransitionStruct(int id);
    static std::vector<Transition> getAllTransitions();
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

    BankAccount senderAcc = BankAccount::getAccountStruct(tempTransition.sender);
    BankAccount receiverAcc = BankAccount::getAccountStruct(tempTransition.receiver);
    senderAcc.balance -= tempTransition.amount;
    receiverAcc.balance += tempTransition.amount;
    BankAccount::addOrUpdateAccount(senderAcc);
    BankAccount::addOrUpdateAccount(receiverAcc);

    Transition::addOrUpdateTransition(tempTransition);
	
    return tempTransition;
}