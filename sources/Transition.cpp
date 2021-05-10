#include "../headers/Transition.h"

int Transition::transitionsCount = 0;
QString Transition::fileName = "data/transitions.json";

QJsonObject Transition::getTransition(int id)
{
	return getObject(Transition::fileName, QString::number(id));
}

void Transition::addOrUpdateTransition(Transition transition)
{
	QJsonObject transitionObj;
	transitionObj["id"] = transition.id;
	transitionObj["sender"] = transition.sender;
	transitionObj["receiver"] = transition.receiver;
	transitionObj["amount"] = transition.amount;
	transitionObj["transitionDate"] = transition.transitionDate;

	BankAccount sender = BankAccount::getAccountStruct(transition.sender);
	BankAccount receiver = BankAccount::getAccountStruct(transition.receiver);
	sender.balance -= transition.amount;
	receiver.balance += transition.amount;
	BankAccount::addOrUpdateAccount(sender);
	BankAccount::addOrUpdateAccount(receiver);
	
	addOrUpdateObject(Transition::fileName, QString::number(transition.id), transitionObj);
}

void Transition::removeTransition(int id)
{
	removeObject(Transition::fileName, QString::number(id));
}

Transition Transition::getTransitionStruct(QJsonObject transitionObj)
{
	Transition tempTransition;
	tempTransition.id = transitionObj["id"].toInt();
	tempTransition.sender = transitionObj["sender"].toInt();
	tempTransition.receiver = transitionObj["receiver"].toInt();
	tempTransition.amount = transitionObj["amount"].toInt();
	tempTransition.transitionDate = transitionObj["transitionDate"].toInt();

	return tempTransition;
}

Transition Transition::getTransitionStruct(int id)
{
	return getTransitionStruct(getTransition(id));
}