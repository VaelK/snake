#ifndef CPUACTOR_H
#define CPUACTOR_H
#include <actor.h>
#include <QString>

class CpuActor: public Actor
{
    Q_OBJECT
public:
    CpuActor(QString name = "new_cpu_actor");
    void train();
    Direction perform(Direction currentDirection, QVector<QVector<int>> position, QVector<QVector<CellType>> boardState);
    ~CpuActor();
    QHash<Direction, int> RankDirection(QVector<QVector<int>> position, QVector<QVector<CellType>> boardState);
    int DotProductDir(QVector<int> dir_1, Direction dir_2);

signals:
    void actorActionResponse(Direction dir);

public slots:
    void requireActorAction(Direction, QVector<QVector<int>>, QVector<QVector<CellType>>);
};

#endif // CPUACTOR_H
