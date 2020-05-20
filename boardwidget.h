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
    explicit BoardWidget(QWidget *parent = nullptr);
    ~BoardWidget();
    void paintEvent(QPaintEvent *e);
    int getBoardWidth() const;
    int getBoardHeight() const;
    CellType getBoardCell(int i, int j) const;
    QVector<QVector<CellType> > getBoardState() const;

private:
    Ui::BoardWidget *ui;
    int boardWidth;
    int boardHeight;
    int actionPerMinutes;
    QVector<QVector<CellType>> boardState;
    bool isEnded;

public slots:
    void setBoardCell(int i, int j, CellType c);
    void gameEnd();
    void startGame();
};

#endif // BOARDWIDGET_H
