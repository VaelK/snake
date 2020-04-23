#include "gamewidget.h"
#include "ui_gamewidget.h"
#include "boardwidget.h"

GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWidget)
{
    ui->setupUi(this);
    BoardWidget *boardWidget = new BoardWidget;
    ui->horizontalLayout->replaceWidget(ui->BoardWidget, boardWidget);
}

GameWidget::~GameWidget()
{
    delete ui;
}
