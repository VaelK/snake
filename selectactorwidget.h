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
    static std::list<Actor> loadActors();

public slots:
    void validateNewActor();
    void cancelNewActor();

private:
    Ui::SelectActorWidget *ui;
    std::list<Actor> listActor;
};

#endif // SELECTACTORWIDGET_H
