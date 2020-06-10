#include "gamewidget.h"
#include "ui_gamewidget.h"
#include "boardwidget.h"
#include "QDebug"
#include "QWidget"

GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWidget)
{
    ui->setupUi(this);
    QObject::connect(ui->statsButt,
                     SIGNAL(pressed()),
                     this, SIGNAL(toStatsWidget()));
    QObject::connect(ui->selectActorButt,
                     SIGNAL(pressed()),
                     this, SIGNAL(toSelectActorWidget()));
    QObject::connect(ui->startButt,
                     SIGNAL(pressed()),
                     this, SIGNAL(startGame()));
    QObject::connect(ui->stopButt,
                     SIGNAL(pressed()),
                     this, SIGNAL(stopGame()));
    QObject::connect(ui->stopButt,
                     SIGNAL(pressed()),
                     this, SLOT(stopGameSlot()));
}

GameWidget::~GameWidget()
{
    delete ui;
}

void GameWidget::getNewActor(Actor *actor){
    this->ui->scoreLabel->setText("Score: 0");
    this->ui->actorLabel->setText("Acteur: "+actor->getName());
    QObject::connect(ui->stopButt,
                     SIGNAL(pressed()),
                     actor, SLOT(stopGameSlot()));
}

void GameWidget::increaseScore(){
    int score = QString(ui->scoreLabel->text().split(" ")[1]).toInt();
    score += 1;
    this->ui->scoreLabel->setText("Score: "+QString::number(score));
    this->increaseBestScore(score);
}

void GameWidget::stopGameSlot(){
    this->ui->scoreLabel->setText("Score: 0");
}
