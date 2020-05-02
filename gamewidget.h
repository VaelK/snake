#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <celltype.h>

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
};

#endif // GAMEWIDGET_H
