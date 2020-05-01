#include "naiveactor.h"
#include "actor.h"
#include <time.h>
#include <stdlib.h>
#include <QString>
#include <QList>
#include <celltype.h>
#include <direction.h>

NaiveActor::NaiveActor(QString name)
    : Actor{name}
{
    //Initializing the random number generator for perform function
    srand(time(NULL));
}

void NaiveActor::train(){

}
Direction NaiveActor::perform(Direction currentDirection, QList<int> position, QList<QList<CellType>> boardState){
    //First we decide if we change direction
    int change_direction = (rand() % 100) > 80;
    if (change_direction){
        switch (rand() % 4) {
        case 0:
            return Direction::left;
        case 1:
            return Direction::right;
        case 2:
            return Direction::up;
        case 3:
            return Direction::down;
        }
    }
    return currentDirection;
}
