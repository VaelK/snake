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
    this->boardWidth = 30;
    this->boardHeight = 30;
    this->boardState = QVector<QVector<CellType>>(this->boardHeight, QVector<CellType>(this->boardWidth));
}

BoardWidget::~BoardWidget()
{
    delete ui;
}

void BoardWidget::paintEvent(QPaintEvent *e)
{
    // Coor parameters
    QColor appleColor = Qt::red;
    QColor snakeColor = Qt::black;
    QColor gridColor = Qt::gray;
    // Draw the mesh
    QPainter painter(this);
    QPen pen(gridColor);
    pen.setWidth(1);
    painter.setPen(pen);
    //horizontal lines
    int& h = this->boardHeight;
    int& w = this->boardWidth;
    QVector<int> xpos = {};
    QVector<int> ypos = {};
    for (int iter=0; iter<=h; iter++){
        QPoint p1;
        p1.setX(0);
        int p = QWidget::height()/h * iter;
        ypos.append(p);
        p1.setY(p);
        QPoint p2;
        p2.setX(qFloor(QWidget::width()/w) * w);
        p2.setY(p);
        painter.drawLine(p1, p2);
    }
    //Vetical lines
    for (int iter=0; iter<=w; iter++){
        QPoint p1;
        int p = QWidget::width()/w * iter;
        xpos.append(p);
        p1.setX(p);
        p1.setY(0);
        QPoint p2;
        p2.setX(p);
        p2.setY(qFloor(QWidget::height()/h) * h);
        painter.drawLine(p1, p2);
    }
    if (this->boardState.length() != 0){
        //Drawing the snake and the apple.
        QPen penApple(appleColor);
        QPen penSnake(snakeColor);
        QPen penGrid(gridColor);
        penApple.setWidth(1);
        QRect rect;
        for (int i=0; i<this->boardState.length(); ++i){
            for (int j=0; j<this->boardState[i].length(); ++j){
                switch(this->boardState[i][j]){
                case CellType::apple:
                    painter.setBrush(appleColor);
                    painter.setPen(penApple);
                    rect = QRect(xpos[j], ypos[i], QWidget::width()/w, QWidget::height()/h);
                    painter.drawRect(rect);
                    break;
                case CellType::snake:
                    painter.setBrush(snakeColor);
                    painter.setPen(penSnake);
                    rect = QRect(xpos[j], ypos[i], QWidget::width()/w, QWidget::height()/h);
                    painter.drawRect(rect);
                    break;
                case CellType::empty:
                    continue;
                }
            }
        }
    }
}

int BoardWidget::getBoardWidth() const
{
    return boardWidth;
}

int BoardWidget::getBoardHeight() const
{
    return boardHeight;
}

void BoardWidget::setBoardCell(int i, int j, CellType value)
{
    this->boardState[i][j] = value;
    this->update();
}
