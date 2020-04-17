#ifndef STATWIDGET_H
#define STATWIDGET_H

#include <QWidget>

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

public slots:
    void leaveStat();

private:
    Ui::StatWidget *ui;
};

#endif // STATWIDGET_H
