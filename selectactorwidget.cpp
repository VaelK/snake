#include "selectactorwidget.h"
#include "ui_selectactorwidget.h"
#include "QPushButton"
#include "QWidget"
#include "QMainWindow"
#include "QStackedWidget"

SelectActorWidget::SelectActorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectActorWidget)
{
    ui->setupUi(this);
    QObject::connect(this->findChild<QPushButton *>("okButt"),
                     SIGNAL(pressed()),
                     this, SLOT(validateNewActor()));
    QObject::connect(this->findChild<QPushButton *>("cancelButt"),
                     SIGNAL(pressed()),
                     this, SLOT(validateNewActor()));
    this->parent = parent;
}

SelectActorWidget::~SelectActorWidget()
{
    delete ui;
}

void SelectActorWidget::validateNewActor(){
    //TODO Add here logic that deal with updating (or not if no change) the current actor
    QStackedWidget *stackedWidget = this->parent->findChild<QStackedWidget *>("stackedWidget");
    stackedWidget->setCurrentIndex(0);
}

void SelectActorWidget::cancelNewActor(){
    QStackedWidget *stackedWidget = this->parent->findChild<QStackedWidget *>("stackedWidget");
    stackedWidget->setCurrentIndex(0);
}
