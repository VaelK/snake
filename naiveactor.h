#ifndef NAIVEACTOR_H
#define NAIVEACTOR_H
#include <actor.h>
#include <QString>

class NaiveActor: Actor
{
public:
    NaiveActor(QString name = "new_naive_actor");
    void train();
    int perform();
    void saveActor();
};

#endif // NAIVEACTOR_H
