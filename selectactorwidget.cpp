#include "selectactorwidget.h"
#include "ui_selectactorwidget.h"
#include "QPushButton"
#include "QWidget"
#include "QMainWindow"
#include "QStackedWidget"
#include "QDir"
#include "QStringRef"
#include "QDebug"
#include "naiveactor.h"
#include "actor.h"
#include "naiveactor.h"

SelectActorWidget::SelectActorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectActorWidget)
{
    ui->setupUi(this);
    QObject::connect(ui->okButt,
                     SIGNAL(pressed()),
                     this, SLOT(validateNewActor()));
    QObject::connect(ui->cancelButt,
                     SIGNAL(pressed()),
                     this, SLOT(cancelNewActor()));
    this->parent = parent;
    this->pathToSave = "./data/actors/";
    QList<Actor> listActor = this->loadActors();
    this->setCurrentActor(listActor[0]);
}

SelectActorWidget::~SelectActorWidget()
{
    delete ui;
}

void SelectActorWidget::validateNewActor(){
    //TODO Add here logic that deal with updating (or not if no change) the current actor
    //Get the name of the selected actor from the list in the UI
    Actor actor = Actor();
    //Create the actor and set it as the current one
    this->setCurrentActor(actor);
    this->toGameWidget();
}

void SelectActorWidget::cancelNewActor(){
    this->toGameWidget();
}
QList<Actor> SelectActorWidget::loadActors()
{
    QList<Actor> listActor;
    QDir dir(this->pathToSave, "*.txt");
    QStringList listFile = dir.entryList();
    for (int i = 0; i < listFile.size(); ++i)
    {
        qDebug() << "Reading file:";
        qDebug() << listFile.at(i);
        Actor actor = Actor(listFile.at(i).left(listFile.at(i).length()-4));
        Actor::loadActor(this->pathToSave, actor);
        listActor.insert(listActor.begin(), actor);

    }
    // test if list is empty, then create a default actor here
    if (listActor.empty()){
        NaiveActor actor= NaiveActor();
        listActor.insert(listActor.begin(), actor);
        Actor::saveActor(this->pathToSave, actor);
    }
    return(listActor);
}

void SelectActorWidget::setCurrentActor(Actor actor){
    this->currentActor = actor;
    this->sendCurrentActor(actor);
}

