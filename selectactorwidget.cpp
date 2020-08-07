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
#include "humanactor.h"
#include "QComboBox"

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
    QList<Actor*> listActor = this->loadActors();
    this->setCurrentActor(listActor[0]);
    QObject::connect(ui->addNewActorButt,
                     SIGNAL(pressed()),
                     this, SLOT(addNewHumanActor()));
    ui->actorNameCB->clear();
    ui->actorTypeCB->clear();
    ui->actorTypeCB->addItem("human");
    ui->actorTypeCB->addItem("ia");
    ui->actorTypeCB->setCurrentText("ia");
    this->refreshCBActor(ActorType::ia);
    //Callback for CB selection
    QObject::connect(ui->actorTypeCB,
                     QOverload<int>::of(&QComboBox::currentIndexChanged),
                     this,
                     QOverload<int>::of(&SelectActorWidget::actorTypeChanged));
}

SelectActorWidget::~SelectActorWidget()
{
    delete ui;
}

void SelectActorWidget::validateNewActor(){
    QList<Actor*> listActor = this->loadActors();
    for (int i=0; i<listActor.length(); i++){
        if (listActor[i]->getName() == ui->actorNameCB->currentText()){
            this->setCurrentActor(listActor[i]);
        }
    }
    this->toGameWidget();
}

void SelectActorWidget::cancelNewActor(){
    this->toGameWidget();
}
QList<Actor*> SelectActorWidget::loadActors()
{
    QList<Actor*> listActor;
    QDir dir(this->pathToSave, "*.txt");
    QStringList listFile = dir.entryList();
    for (int i = 0; i < listFile.size(); ++i)
    {
        Actor& actor = Actor::loadActorFromFile(this->pathToSave+listFile.at(i));
        listActor.append(&actor);
    }
    // test if list is empty, then create a default actor here
    if (listActor.empty()){
        NaiveActor *actor= new NaiveActor();
        listActor.append(actor);
        Actor::saveActor(this->pathToSave, *actor);
    }
    return(listActor);
}

void SelectActorWidget::setCurrentActor(Actor *actor){
    if (actor){
        delete this->currentActor;
        this->currentActor = actor;
        this->sendCurrentActor(actor);
    }else{
        this->sendCurrentActor(this->currentActor);
    }
}

// Logic of the combo boxs

void SelectActorWidget::refreshCBActor(ActorType type){
    // Visibility of new acotr input
    if (type == ActorType::human){
        this->ui->addActorLabel->setVisible(true);
        this->ui->nameNewActor->setVisible(true);
        this->ui->addNewActorButt->setVisible(true);
    }else{
        this->ui->addActorLabel->setVisible(false);
        this->ui->nameNewActor->setVisible(false);
        this->ui->addNewActorButt->setVisible(false);
    }
    QList<Actor*> listActor = this->loadActors();
    this->ui->actorNameCB->clear();
    for (int i=0; i<listActor.length(); i++){
        if (listActor[i]->getType() == type){
            this->ui->actorNameCB->addItem(listActor[i]->getName());
        }
    }
}

void SelectActorWidget::addNewHumanActor(){
    QString name = this->ui->nameNewActor->text();
    //Check if name is valide
    QList<Actor*> listActor = this->loadActors();
    if (name==""){
        return;
    }
    for (int i=0; i<listActor.length(); i++){
        if (listActor[i]->getName() == name){
            this->ui->nameNewActor->setText("");
            return;
        }
    }
    HumanActor *actor = new HumanActor(name);
    //Saving actor
    //Cleaning the input field
    this->ui->nameNewActor->setText("");
    // Saving the actor name
    Actor::saveActor("data/actors/", *actor);
    //Refreshing list
    this->refreshCBActor(ActorType::human);
}

void SelectActorWidget::actorTypeChanged(int index){
    this->refreshCBActor(static_cast<ActorType>(index));
}

void SelectActorWidget::increaseBestScore(int score){
    if (this->currentActor->getBestScore() < score)
        this->currentActor->setBestScore(score);
}

void SelectActorWidget::requestActorList(){
    this->sendActorList(this->loadActors());
}
