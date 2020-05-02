#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H
#include <QWidget>
#include <celltype.h>

namespace Ui {
class BoardWidget;
}

class BoardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BoardWidget(QWidget *parent = nullptr, QList<QList<CellType>> boardState = {});
    ~BoardWidget();
    void paintEvent(QPaintEvent *e);

private:
    Ui::BoardWidget *ui;
    int boardWidth;
    int boardHeight;
    int actionPerMinutes;
    QList<QList<CellType>> boardState;

public slots:
    void newBoardStat(QList<QList<CellType>>);
};

#endif // BOARDWIDGET_H
