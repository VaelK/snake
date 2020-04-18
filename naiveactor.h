#ifndef NAIVEACTOR_H
#define NAIVEACTOR_H
#include <actor.h>

class NaiveActor: Actor
{
public:
    NaiveActor(std::string name = "new_naive_actor");
    void train();
    int perform();
    void saveActor();
};

#endif // NAIVEACTOR_H
