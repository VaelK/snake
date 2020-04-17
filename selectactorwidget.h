#ifndef SELECTACTORWIDGET_H
#define SELECTACTORWIDGET_H

#include <QWidget>
#include <QMainWindow>

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

public slots:
    void validateNewActor();
    void cancelNewActor();

private:
    Ui::SelectActorWidget *ui;
};

#endif // SELECTACTORWIDGET_H
