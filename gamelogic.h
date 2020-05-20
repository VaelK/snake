#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include <QObject>
#include <QList>
#include <direction.h>
#include <celltype.h>
#include <boardwidget.h>
#include <actor.h>

class GameLogic : public QObject
{
    Q_OBJECT
private:
    QVector<QVector<int>> snakePosition;
    Direction currentDirection;
    int boardWidth;
    int boardHeight;
    int actionPerMinutes;
    BoardWidget *boardWidget;
    bool isStarted;
    QTimer *timer;

public:
    GameLogic(BoardWidget *parent = nullptr);
    virtual ~GameLogic() {}
    void drawSnakeInit();
    void initSnakePosition();
signals:
    void setBoardCell(int i, int j, CellType c);
    void requireActorAction(Direction, QVector<QVector<int>>, QVector<QVector<CellType>>);
    void gameEnd();
    void increaseScore();
public slots:
    void requireActorActionSlot();
    void startGame();
    void stopGame();
    void actorActionResponse(Direction);
    void getNewActor(Actor *actor);
};

#endif // GAMELOGIC_H
