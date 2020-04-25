#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H
#include <QWidget>

namespace Ui {
class BoardWidget;
}

class BoardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BoardWidget(QWidget *parent = nullptr);
    ~BoardWidget();
    void paintEvent(QPaintEvent *e);

private:
    Ui::BoardWidget *ui;
    int boardWidth;
    int boardHeight;
    int actionPerMinutes;
};

#endif // BOARDWIDGET_H
