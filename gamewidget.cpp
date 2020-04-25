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
    BoardWidget *boardWidget = new BoardWidget();
    //QLayoutItem* old = ui->horizontalLayout->replaceWidget(ui->BoardWidget, boardWidget);
    //delete old;

    QObject::connect(ui->statsButt,
                     SIGNAL(pressed()),
                     this, SIGNAL(toStatsWidget()));
    QObject::connect(ui->selectActorButt,
                     SIGNAL(pressed()),
                     this, SIGNAL(toSelectActorWidget()));
}

GameWidget::~GameWidget()
{
    delete ui;
}

