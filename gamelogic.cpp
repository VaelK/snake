#include "gamelogic.h"
#include "actor.h"
#include "QList"
#include "QWidget"
#include "qmath.h"
#include "boardwidget.h"
#include "QDebug"

GameLogic::GameLogic(BoardWidget *parent)
    : QObject(parent){
    this->boardWidth = parent->getBoardWidth();
    this->boardHeight = parent->getBoardHeight();
    this->actionPerMinutes = 120;
    this->snakePosition = {this->boardWidth/2, this->boardHeight/2};
    this->currentDirection = Direction::up;
    this->snakeLen = 3;
    this->boardWidget = parent;
    this->drawSnake();
}
void GameLogic::startGame(){

}
void GameLogic::stopGame(){

}

void GameLogic::drawSnake(){
    for (int i=0; i<this->snakeLen; i++){
        this->setBoardCell(this->snakePosition[0]-i, this->snakePosition[1], CellType::snake);
    }
}
