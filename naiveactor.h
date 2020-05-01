#ifndef NAIVEACTOR_H
#define NAIVEACTOR_H
#include <actor.h>
#include <QString>
#include <direction.h>
#include <celltype.h>

class NaiveActor: public Actor
{
public:
    NaiveActor(QString name = "new_naive_actor");
    void train();
    Direction perform(Direction currentDirection, QList<Direction> position, QList<QList<CellType>> boardState);
};

#endif // NAIVEACTOR_H
