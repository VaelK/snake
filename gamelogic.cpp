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
    this->boardState = {};
    //this->initBoardStat();
    this->newBoardState(this->boardState);
}
void GameLogic::startGame(){

}
void GameLogic::stopGame(){

}

void GameLogic::initBoardStat(){
    this->boardState = {};
    for (int i=0; i<this->boardHeight; i++){
        QList<CellType> row = {};
        for (int j=0; j<this->boardWidth; j++){
            row.insert(0, CellType::empty);
        }
        this->boardState.insert(0, row);
    }
    for (int i=0; i<this->snakeLen; i++){
        this->boardState[this->snakePosition[0]-i][this->snakePosition[1]] = CellType::snake;
    }
    qDebug() << "Sending board";
    this->newBoardState(this->boardState);
}
