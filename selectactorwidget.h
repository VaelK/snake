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
    QList<Actor> loadActors();

public slots:
    void validateNewActor();
    void cancelNewActor();

signals:
    void sendCurrentActor(Actor actor);
    void toGameWidget();

private:
    Ui::SelectActorWidget *ui;
    QList<Actor> listActor;
    QString pathToSave;
    Actor currentActor;
    void setCurrentActor(Actor);
};

#endif // SELECTACTORWIDGET_H
