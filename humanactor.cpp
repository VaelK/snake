#include "humanactor.h"
#include <QString>
#include <actor.h>
#include <QDebug>

HumanActor::HumanActor(QString name)
: Actor{name}
{
}

HumanActor::~HumanActor(){}

void HumanActor::train(){

}
Direction HumanActor::perform(Direction currentDirection, QVector<QVector<int>> position, QVector<QVector<CellType>> boardState){
    return currentDirection;
}

void HumanActor::requireActorAction(Direction dir, QVector<QVector<int>> position, QVector<QVector<CellType>> boardState){
    this->actorActionResponse(this->perform(dir, position, boardState));
}
