#ifndef SELECTACTORWIDGET_H
#define SELECTACTORWIDGET_H

#include <QWidget>
#include <QMainWindow>
#include <actor.h>

namespace Ui {
class SelectActorWidget;
}

class SelectActorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SelectActorWidget(QWidget *parent = nullptr);
    ~SelectActorWidget();
    QWidget *parent;
    QList<Actor*> loadActors();
    void setCurrentActor(Actor *actor = NULL);
    void refreshCBActor(ActorType);

public slots:
    void validateNewActor();
    void cancelNewActor();
    void addNewHumanActor();
    void actorTypeChanged(int index);
    void increaseBestScore(int);
    void requestActorList();

signals:
    void sendCurrentActor(Actor *actor);
    void toGameWidget();
    void sendActorList(QList<Actor*>);

private:
    Ui::SelectActorWidget *ui;
    QList<Actor> listActor;
    QString pathToSave;
    Actor *currentActor;
};

#endif // SELECTACTORWIDGET_H
