#include "../headers/Transition.h"

int Transition::transitionsCount = 0;
QString Transition::fileName = "data/transitions.json";

QJsonObject Transition::getTransition(int id)
{
	return getObject(Transition::fileName, QString::number(id));
}

void Transition::addTransition(Transition transition)
{
	QJsonObject transitionObj;
	transitionObj["id"] = transition.id;
	transitionObj["sender"] = transition.sender;
	transitionObj["receiver"] = transition.receiver;
	transitionObj["amount"] = transition.amount;
	transitionObj["transitionDate"] = transition.transitionDate;

	addObject(Transition::fileName, QString::number(transition.id), transitionObj);
}

void removeTransition(int id)
{
	removeObject(Transition::fileName, QString::number(id));
}