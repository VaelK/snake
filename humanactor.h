#ifndef HUMANACTOR_H
#define HUMANACTOR_H
#include <actor.h>
#include <QKeyEvent>
class HumanActor: public Actor
{
     Q_OBJECT
public:
    HumanActor(QString name = "new_human_actor");
    void train();
    Direction perform(Direction currentDirection, QVector<QVector<int>> position, QVector<QVector<CellType>> boardState);
    ~HumanActor();
private:
    Direction currentDirection;

protected:
    bool keyReleaseEvent(QKeyEvent  *event);
    bool eventFilter(QObject* obj, QEvent* event);

signals:
    void actorActionResponse(Direction dir);

public slots:
    void requireActorAction(Direction, QVector<QVector<int>>, QVector<QVector<CellType>>);
};

#endif // HUMANACTOR_H
