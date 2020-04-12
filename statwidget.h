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

private:
    Ui::StatWidget *ui;
};

#endif // STATWIDGET_H
