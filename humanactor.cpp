#include "humanactor.h"
#include <QString>
#include <actor.h>
#include <QDebug>
#include <QEvent>
#include <QKeyEvent>

HumanActor::HumanActor(QString name)
    : Actor{name}
{
    this->setType(ActorType::human);
    this->currentDirection = Direction::up;
}

HumanActor::~HumanActor(){}

void HumanActor::train(){

}
Direction HumanActor::perform(Direction currentDirection, QVector<QVector<int>> position, QVector<QVector<CellType>> boardState){
    return currentDirection;
}

void HumanActor::requireActorAction(Direction dir, QVector<QVector<int>> position, QVector<QVector<CellType>> boardState){
    QVector<QString> dir_list(4);
    dir_list[0] = "left";
    dir_list[1] = "right";
    dir_list[2] = "up";
    dir_list[3] = "down";
    if ((dir == Direction::up) && (this->currentDirection == Direction::down)){
        this->currentDirection = Direction::up;
    }
    if ((dir == Direction::down) && (this->currentDirection == Direction::up)){
        this->currentDirection = Direction::down;
    }
    if ((dir == Direction::left) && (this->currentDirection == Direction::right)){
        this->currentDirection = Direction::left;
    }
    if ((dir == Direction::right) && (this->currentDirection == Direction::left)){
        this->currentDirection = Direction::right;
    }
    this->actorActionResponse(this->perform(this->currentDirection, position, boardState));
}

bool HumanActor::keyReleaseEvent(QKeyEvent *ev)
{
    switch (ev->key()) {
    case Qt::Key_Left:
        this->currentDirection = Direction::left;
        return true;
        break;
    case Qt::Key_Right:
        this->currentDirection = Direction::right;
        return true;
        break;
    case Qt::Key_Up:
        this->currentDirection = Direction::up;
        return true;
        break;
    case Qt::Key_Down:
        this->currentDirection = Direction::down;
        return true;
        break;
    default:
        return false;
    }
}

bool HumanActor::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type()==QEvent::KeyRelease) {
        QKeyEvent* key = static_cast<QKeyEvent*>(event);
        return this->keyReleaseEvent(key);
    } else {
        return QObject::eventFilter(obj, event);
    }
    return false;
}
