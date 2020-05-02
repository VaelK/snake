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
    QList<int> snakePosition;
    Direction currentDirection;
    QList<QList<CellType>> boardState;
    int boardWidth;
    int boardHeight;
    int actionPerMinutes;
    int snakeLen;

public:
    GameLogic(BoardWidget *parent = nullptr);
    virtual ~GameLogic() {}
    void initBoardStat();

public slots:
    void startGame();
    void stopGame();

signals:
    void newBoardState(QList<QList<CellType>>);
};

#endif // GAMELOGIC_H
