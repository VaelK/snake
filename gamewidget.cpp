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
}

GameWidget::~GameWidget()
{
    delete ui;
}

