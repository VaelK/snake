#include "boardwidget.h"
#include "ui_boardwidget.h"
#include "QStyleOption"
#include "QPainter"
#include "QDebug"
#include "QtMath"

BoardWidget::BoardWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BoardWidget)
{
    ui->setupUi(this);
}

BoardWidget::~BoardWidget()
{
    delete ui;
}

void BoardWidget::paintEvent(QPaintEvent *e)
{
    // Draw the mesh
    QPainter painter(this);
    QPen pen(Qt::black);
    pen.setWidth(1);
    painter.setPen(pen);
    //horizontal lines
    int h = GameParameters::Instance().getBoardHeight();
    int w = GameParameters::Instance().getBoardWidth();
    for (int iter=0; iter<=h; iter++){
        QPoint p1;
        p1.setX(0);
        p1.setY(QWidget::height()/h * iter);
        QPoint p2;
        p2.setX(qFloor(QWidget::width()/w) * w);
        p2.setY(QWidget::height()/h * iter);
        painter.drawLine(p1, p2);
    }
    //Vetical lines
    for (int iter=0; iter<=w; iter++){
        QPoint p1;
        p1.setX(this->geometry().width()/w * iter);
        p1.setY(0);
        QPoint p2;
        p2.setX(this->geometry().width()/w * iter);
        p2.setY(qFloor(this->geometry().height()/h) * h);
        painter.drawLine(p1, p2);
    }
    qDebug() << w;
    qDebug() << "Drawing " << QWidget::width()/w;
    qDebug() << QWidget::height()/w;
    qDebug() << this->geometry().width();
}
