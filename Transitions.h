#include <iostream>

struct Transition
{
    int id;
    static int transitionsCount;

    int sender;   // Foreign Key
    int receiver; // Foreign Key
    int amount;
    time_t transitionDate = time(0);
};
int Transition::transitionsCount = 0;

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