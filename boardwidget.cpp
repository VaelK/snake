#include "boardwidget.h"
#include "ui_boardwidget.h"
#include "QStyleOption"
#include "QPainter"
#include "QDebug"
#include "QtMath"
#include "QBrushData"

BoardWidget::BoardWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BoardWidget)
{
    ui->setupUi(this);
    this->boardWidth = 40;
    this->boardHeight = 30;
    this->boardState = QVector<QVector<CellType>>(this->boardWidth, QVector<CellType>(this->boardHeight)); // convention x, y. x = abscisse, y = ordonne
    this->isEnded = false;
    int rockWidth = 4;
    int rockHeight = 6;
    int nbRockRow = 3;
    int nbRockCol = 5;
    QVector<int> rockColSpace = QVector<int>(nbRockCol, 4);
    rockColSpace[0] = 2;
    for (int i=1; i< rockColSpace.length(); i++){
        rockColSpace[i] = rockColSpace[i-1] + rockColSpace[i];
    }
    QVector<int> rockRowSpace = QVector<int>(nbRockRow, 3);
    for (int i=1; i< rockRowSpace.length(); i++){
        rockRowSpace[i] = rockRowSpace[i-1] + rockRowSpace[i];
    }
    qDebug() << "test";
    for (int rockRow=0; rockRow<nbRockRow; rockRow++){
        for (int rockCol=0; rockCol<nbRockCol; rockCol++){
            int leftPos = rockColSpace[rockCol]+(rockCol)*rockWidth;
            int topPos = rockRowSpace[rockRow]+(rockRow)*rockHeight;
            qDebug() << "Left pos:"+QString::number(leftPos);
            qDebug() << "Top pos:"+QString::number(topPos);
            for (int rockX=0; rockX<rockWidth; rockX++){
                for (int rockY=0; rockY<rockHeight; rockY++){
                    this->boardState[leftPos+rockX][topPos+rockY] = CellType::rock;
                }
            }
        }
    }
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
    QColor rockColor = Qt::black;
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
        QBrush brushRock(Qt::BDiagPattern);
        QPen penRock(rockColor);
        brushRock.setColor(rockColor);
        penApple.setWidth(1);
        QRect rect;
        for (int x=0; x<this->boardState.length(); ++x){
            for (int y=0; y<this->boardState[x].length(); ++y){
                switch(this->boardState[x][y]){
                case CellType::apple:
                    painter.setBrush(appleColor);
                    painter.setPen(penApple);
                    rect = QRect(xpos[x], ypos[y], QWidget::width()/w, QWidget::height()/h);
                    painter.drawRect(rect);
                    break;
                case CellType::snake:
                    painter.setBrush(snakeColor);
                    painter.setPen(penSnake);
                    rect = QRect(xpos[x], ypos[y], QWidget::width()/w, QWidget::height()/h);
                    painter.drawRect(rect);
                    break;
                case CellType::rock:
                    painter.setBrush(brushRock);
                    painter.setPen(penRock);
                    rect = QRect(xpos[x], ypos[y], QWidget::width()/w, QWidget::height()/h);
                    painter.drawRect(rect);
                    break;
                case CellType::empty:
                    continue;
                }
            }
        }
    }
    //Treat the end game:
    if (this->isEnded){
        QColor c = QColor("#7D505050");
        QRect rect = QRect(0, 0, QWidget::width(), QWidget::height());
        QPen penEndGame(c);
        painter.setBrush(c);
        painter.setPen(penEndGame);
        painter.drawRect(rect);
        // Text Game over
        QPen penText(Qt::black);
        painter.setPen(penText);
        QRectF rect_text = QRectF(QWidget::width()*0.33, QWidget::height()*0.33,
                           QWidget::width()*0.33, QWidget::height()*0.33);
        painter.drawText(rect_text, Qt::AlignCenter, tr("Game Over"));
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

QVector<QVector<CellType> > BoardWidget::getBoardState() const
{
    return boardState;
}

void BoardWidget::setBoardCell(int x, int y, CellType value)
{
    this->boardState[x][y] = value;
    this->update();
}

CellType BoardWidget::getBoardCell(int x, int y) const
{
    return this->boardState[x][y];
}

void BoardWidget::gameEnd()
{
    this->isEnded = true;
    this->update();
}

void BoardWidget::startGame(){
    this->isEnded = false;
    this->update();
}

QVector<QVector<int>> BoardWidget::getEmptyCells(){
    QVector<QVector<int>> result;
    for (int x=0; x<this->boardState.length(); ++x){
        for (int y=0; y<this->boardState[x].length(); ++y){
            if (this->getBoardCell(x, y) == CellType::empty){
                QVector<int> pos = QVector<int>(2);
                pos[0] = x;
                pos[1] = y;
                result.append(pos);
            }
        }
    }
    return result;
}
