#include "gamelogic.h"
#include "actor.h"
#include "QList"
#include "QWidget"
#include "qmath.h"
#include "boardwidget.h"
#include "QDebug"
#include "QThread"
#include <windows.h>
#include <QTimer>
#include <typeinfo>
#include <naiveactor.h>
#include <QException>
#include <humanactor.h>

GameLogic::GameLogic(BoardWidget *parent)
    : QObject(parent){
    this->boardWidth = parent->getBoardWidth();
    this->boardHeight = parent->getBoardHeight();
    this->actionPerMinutes = 600;
    this->initSnakePosition();
    this->currentDirection = Direction::up;
    this->boardWidget = parent;
    this->isStarted = false;
    this->timer = new QTimer(this);
    connect(this->timer, &QTimer::timeout, this, QOverload<>::of(&GameLogic::requireActorActionSlot));
}

void GameLogic::initSnakePosition(){
    this->snakePosition = {{this->boardWidth/2, this->boardHeight/2},
                           {this->boardWidth/2, this->boardHeight/2+1},
                           {this->boardWidth/2, this->boardHeight/2+2}};
}

void GameLogic::startGame(){
    this->isStarted = true;
    //Set timer to process motion every x ms
    this->timer->start(60.0/this->actionPerMinutes*1000);
}

void GameLogic::requireActorActionSlot(){
    //0. Actualise the currentDirection with actor
    this->requireActorAction(this->currentDirection, this->snakePosition, this->boardWidget->getBoardState());
}

void GameLogic::stopGame(){
    this->isStarted = false;
    this->timer->stop();
    for (int i=0; i<this->snakePosition.length(); i++){
        this->setBoardCell(this->snakePosition[i][0],
                this->snakePosition[i][1], CellType::empty);
    }
    this->initSnakePosition();
    this->drawSnakeInit();
}

void GameLogic::drawSnakeInit(){
    for (int i=0; i<this->snakePosition.length(); i++){
        this->setBoardCell(this->snakePosition[i][0], this->snakePosition[i][1], CellType::snake);
    }
}

void GameLogic::actorActionResponse(Direction dir){
    //0. Compute position of next grid point
    this->currentDirection = dir;
    QVector<int> currentHeadPosition = this->snakePosition[0];
    switch (dir) {
    case Direction::left:
        currentHeadPosition[0] -= 1;
        break;
    case Direction::right:
        currentHeadPosition[0] += 1;
        break;
    case Direction::up:
        currentHeadPosition[1] -= 1;
        break;
    case Direction::down:
        currentHeadPosition[1] += 1;
        break;
    default:
        throw QException{};
    }
    //Check border:
    if ((currentHeadPosition[0] < 0)||(currentHeadPosition[1] < 0) || (currentHeadPosition[0] >= this->boardWidth) || (currentHeadPosition[1] >= this->boardHeight)){
        this->gameEnd();
        return;
    }
    switch (this->boardWidget->getBoardCell(currentHeadPosition[0], currentHeadPosition[1]))
    {
    //1. check the next case.
    case CellType::snake:
        //   If snake => game ends (function game ends with saving scores and so on)
        this->gameEnd();
        break;
    case CellType::apple:
        //   If apple => insert the grid point to snakePosition (index 0), send signal to update score
        this->snakePosition.prepend(currentHeadPosition);
        this->setBoardCell(currentHeadPosition[0], currentHeadPosition[1], CellType::snake);
        this->increaseScore();
        this->createApple();
        break;
    case CellType::empty:
        //   If empty => push the grid point to snakePosition and pop its rear position
        this->snakePosition.prepend(currentHeadPosition);
        this->setBoardCell(currentHeadPosition[0], currentHeadPosition[1], CellType::snake);
        this->setBoardCell(this->snakePosition[this->snakePosition.size()-1][0],
                this->snakePosition[this->snakePosition.size()-1][1], CellType::empty);
        this->snakePosition.removeLast();
        break;
    }
}

void GameLogic::getNewActor(Actor *actor){
    QObject::connect(this,
                     &GameLogic::gameEnd,
                     actor,
                     &Actor::stopGameSlot);
    NaiveActor* test = new NaiveActor();
    QString actorType = QString(typeid(*actor).name());
    if (actorType.compare(QString(typeid(*test).name()))==0){
        NaiveActor* naiveActor = dynamic_cast<NaiveActor*>(actor);
        QObject::connect(this,
                         &GameLogic::requireActorAction,
                         naiveActor,
                         &NaiveActor::requireActorAction);
        QObject::connect(naiveActor,
                         &NaiveActor::actorActionResponse,
                         this,
                         &GameLogic::actorActionResponse);
    }else{
        delete  test;
        Actor* test = new HumanActor();
        if(actorType.compare(QString(typeid(*test).name()))==0){
            HumanActor* humanActor = dynamic_cast<HumanActor*>(actor);
            this->parent()->parent()->installEventFilter(humanActor);
            QObject::connect(this,
                             &GameLogic::requireActorAction,
                             humanActor,
                             &HumanActor::requireActorAction);
            QObject::connect(humanActor,
                             &HumanActor::actorActionResponse,
                             this,
                             &GameLogic::actorActionResponse);
        }else{
            throw QException{};
        }
    }
}

void GameLogic::createApple(){
    QVector<QVector<int>> emptyCells = this->boardWidget->getEmptyCells();
    srand(time(NULL));
    int pos = rand() % emptyCells.length();
    this->boardWidget->setBoardCell(emptyCells[pos][0], emptyCells[pos][1], CellType::apple);
}
