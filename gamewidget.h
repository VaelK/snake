#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <celltype.h>
#include <actor.h>

namespace Ui {
class GameWidget;
}

class GameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GameWidget(QWidget *parent = nullptr);
    ~GameWidget();

private:
    Ui::GameWidget *ui;

signals:
    void toStatsWidget();
    void toSelectActorWidget();
    void startGame();
    void stopGame();
    void increaseBestScore(int);

public slots:
    void getNewActor(Actor *actor);
    void increaseScore();
    void stopGameSlot();
};

#endif // GAMEWIDGET_H
