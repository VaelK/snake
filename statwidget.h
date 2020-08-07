#ifndef STATWIDGET_H
#define STATWIDGET_H

#include <QWidget>
#include <actor.h>

namespace Ui {
class StatWidget;
}

class StatWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StatWidget(QWidget *parent = nullptr);
    ~StatWidget();
    QWidget *parent;
    void refreshPlot();

signals:
    void toGameWidget();
    void requestActorList();

public slots:
    void getActorList(QList<Actor*>);
    void switchWidget();
    void toStatsWidget();

private:
    Ui::StatWidget *ui;
};

#endif // STATWIDGET_H
