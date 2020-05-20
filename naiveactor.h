#ifndef NAIVEACTOR_H
#define NAIVEACTOR_H
#include <actor.h>
#include <QString>
#include <direction.h>
#include <celltype.h>

class NaiveActor: public Actor
{
    Q_OBJECT
public:
    NaiveActor(QString name = "new_naive_actor");
    void train();
    Direction perform(Direction currentDirection, QVector<QVector<int>> position, QVector<QVector<CellType>> boardState);
    ~NaiveActor();

signals:
    void actorActionResponse(Direction dir);

public slots:
    void requireActorAction(Direction, QVector<QVector<int>>, QVector<QVector<CellType>>);
};

#endif // NAIVEACTOR_H
