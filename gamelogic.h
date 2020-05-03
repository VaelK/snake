#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include <QObject>
#include <QList>
#include <direction.h>
#include <celltype.h>
#include <boardwidget.h>

class GameLogic : public QObject
{
    Q_OBJECT
private:
    QVector<int> snakePosition;
    Direction currentDirection;
    int boardWidth;
    int boardHeight;
    int actionPerMinutes;
    int snakeLen;
    BoardWidget *boardWidget;

public:
    GameLogic(BoardWidget *parent = nullptr);
    virtual ~GameLogic() {}
    void drawSnake();

signals:
    void setBoardCell(int i, int j, CellType c);

public slots:
    void startGame();
    void stopGame();
};

#endif // GAMELOGIC_H
