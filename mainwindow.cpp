#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamewidget.h"
#include "statwidget.h"
#include "selectactorwidget.h"
#include "QPushButton"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Stacking the different windows
    GameWidget *gameWidget = new GameWidget();
    StatWidget *statWidget = new StatWidget();
    SelectActorWidget *selectActorWidget = new SelectActorWidget();
    ui->stackedWidget->removeWidget(ui->stackedWidget->currentWidget());
    ui->stackedWidget->removeWidget(ui->stackedWidget->currentWidget());
    ui->stackedWidget->addWidget(gameWidget);
    ui->stackedWidget->addWidget(statWidget);
    ui->stackedWidget->addWidget(selectActorWidget);
    ui->stackedWidget->setCurrentWidget(gameWidget);
    //Connecting widgets together with button
    // Game and actor selection widgets
    QObject::connect(gameWidget->findChild<QPushButton *>("selectActorButt"),
                     QPushButton::pressed,
                     this, MainWindow::toSelectActorWidget);

    // Game and stats widget
    QObject::connect(gameWidget->findChild<QPushButton *>("statsButt"),
                     QPushButton::pressed,
                     this, MainWindow::toStatsWidget);

}

MainWindow::~MainWindow()
{
    delete ui;
}

// Slots
// Control to move from one widget to another
void MainWindow::toGameWidget(){
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::toSelectActorWidget(){
    ui->stackedWidget->setCurrentIndex(2);
}
void MainWindow::toStatsWidget(){
    ui->stackedWidget->setCurrentIndex(1);
}

