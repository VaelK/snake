#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include <QObject>
#include <QList>
#include <direction.h>
#include <celltype.h>

class GameLogic : public QObject
{
    Q_OBJECT
private:
    QList<int> snakePosition;
    Direction currentDirection;
    QList<QList<CellType>> boardState;
    int boardWidth;
    int boardHeight;
    int actionPerMinutes;
    int snakeLen;

public:
    GameLogic(QObject *parent = nullptr, int boardWidth=0, int boardHeight=0, int actionPerMinutes=0);
    virtual ~GameLogic() {}
    void initBoardStat();

public slots:
    void startGame();
    void stopGame();
};

#endif // GAMELOGIC_H
