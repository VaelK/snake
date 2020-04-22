#include "naiveactor.h"
#include "actor.h"
#include <time.h>
#include <stdlib.h>
#include <QString>

NaiveActor::NaiveActor(QString name)
    : Actor{name}
{
    //Initializing the random number generator for perform function
    srand(time(NULL));
}

void NaiveActor::train(){

}
int NaiveActor::perform(){
    //First we decide if we change direction
    int change_direction = (rand() % 100) > 80;
    if (change_direction)
        this->setCurrentDirection(rand() % 4);
    return(this->getCurrentDirection());
}
void NaiveActor::saveActor(){

}
