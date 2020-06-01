#include "naiveactor.h"
#include "actor.h"
#include <time.h>
#include <stdlib.h>
#include <QString>
#include <QList>
#include <celltype.h>
#include <direction.h>
#include "QDebug"

NaiveActor::NaiveActor(QString name)
    : Actor{name}
{
    //Initializing the random number generator for perform function
    srand(time(NULL));
    this->setType(ActorType::ia);
}

NaiveActor::~NaiveActor(){}

void NaiveActor::train(){

}
Direction NaiveActor::perform(Direction currentDirection, QVector<QVector<int>> position, QVector<QVector<CellType>> boardState){
    //First we decide if we change direction
    int change_direction = (rand() % 100) > 80;
    if (change_direction){
        switch (rand() % 4) {
        case 0:
            if (currentDirection != Direction::right)
                return Direction::left;
            else{
                return Direction::right;
            }
            break;
        case 1:
            if (currentDirection != Direction::left)
                return Direction::right;
            else{
                return Direction::left;
            }
            break;
        case 2:
            if (currentDirection != Direction::down)
                return Direction::up;
            else{
                return Direction::down;
            }
            break;
        case 3:
            if (currentDirection != Direction::up)
                return Direction::down;
            else{
                return Direction::up;
            }
            break;
        }
    }
    return currentDirection;
}

void NaiveActor::requireActorAction(Direction dir, QVector<QVector<int>> position, QVector<QVector<CellType>> boardState){
    this->actorActionResponse(this->perform(dir, position, boardState));
}
