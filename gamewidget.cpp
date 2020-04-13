#include "gamewidget.h"
#include "ui_gamewidget.h"
#include "QStyleOption"
#include "QPainter"

GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWidget)
{
    ui->setupUi(this);
}

GameWidget::~GameWidget()
{
    delete ui;
}

void GameWidget::paintEvent(QPaintEvent *e)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    //p.fillRect(e->rect(), QBrush(QColor(64, 32, 64)));
}
