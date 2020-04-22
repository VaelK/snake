#include "selectactorwidget.h"
#include "ui_selectactorwidget.h"
#include "QPushButton"
#include "QWidget"
#include "QMainWindow"
#include "QStackedWidget"
#include "QDir"
#include "QStringRef"
#include "QDebug"

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
    SelectActorWidget::loadActors();
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
std::list<Actor> SelectActorWidget::loadActors()
{
    std::list<Actor> listActor;
    QDir dir("/data/actors");
    QStringList listFile = dir.entryList();
    for (int i = 0; i < listFile.size(); ++i)
    {
        QStringRef subString(&listFile.at(i),0,listFile.at(i).size()-4);
        qDebug() << listFile.at(i).left(listFile.at(i).size()-4);
        Actor *act = new Actor(listFile.at(i).left(listFile.at(i).size()-4));
        act->loadActor();
        listActor.insert(listActor.begin(), *act);
    }
    return(listActor);
}

