#ifndef SELECTACTORWIDGET_H
#define SELECTACTORWIDGET_H

#include <QWidget>

namespace Ui {
class SelectActorWidget;
}

class SelectActorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SelectActorWidget(QWidget *parent = nullptr);
    ~SelectActorWidget();

private:
    Ui::SelectActorWidget *ui;
};

#endif // SELECTACTORWIDGET_H
