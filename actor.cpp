#include "actor.h"
#include <sstream>
#include <utility>
#include <fstream>
#include "QString"
#include <QTextStream>
#include <QHash>
#include <QFile>
#include <QDirIterator>
#include <QDebug>
#include <typeinfo>
#include <QException>
#include <naiveactor.h>
#include <QVector>
#include <humanactor.h>
#include <cpuactor.h>

QTextStream& operator<<(QTextStream& out, const Actor& actor)
{
    out << actor.getName() << " ";
    out << typeid(actor).name() << " ";
    if (actor.getParams().count() > 0){
        for(QHash<QString, double>::iterator iter=actor.getParams().begin(); iter!=actor.getParams().end(); iter++){
            out << iter.key() << " ";
            out << QString::number(iter.value()) << " ";
        }
    }
    return out;
}

QTextStream &operator>>(QTextStream& in, Actor& actor)
{
    QString name;
    QHash<QString, double> params;
    QString classname;
    in >> name;
    in >> classname;
    if (classname != typeid(actor).name())
        throw QException{};
    while (!(in.atEnd())) {
        QString key;
        QString val;
        in >> key;
        in >> val;
        if ((key.length()==0) || (val.length()==0))
            continue;
        bool ok = false;
        params.insert(key, val.toDouble(&ok));
    }
    actor.setName(name);
    actor.setParams(params);
    return in;
}

QHash<QString, double> Actor::getParams() const
{
    return params;
}

void Actor::setParams(const QHash<QString, double> &value)
{
    params = value;
}

QString Actor::getName() const
{
    return name;
}

void Actor::setName(const QString &value)
{
    name = value;
}

ActorType Actor::getType() const
{
    return type;
}

void Actor::setType(const ActorType &value)
{
    type = value;
}

void Actor::setBestScore(int value)
{
    bestScore = value;
}

int Actor::getBestScore() const
{
    return bestScore;
}

int Actor::getTotalNumAction() const
{
    return totalNumAction;
}

void Actor::setTotalNumAction(int value)
{
    totalNumAction = value;
}

Actor::Actor(QString name, QHash<QString, double> params)
{
    this->name = name;
    this->params = params;
    this->bestScore = 0;
    this->totalNumAction = 0;
}

Actor::~Actor(){}

void Actor::saveActor(QString pathToSave, Actor &actor){
    //Loading actor
    QFile file(pathToSave+actor.getName()+".txt");
    file.open(file.ReadWrite);
    QTextStream out(&file);
    out << actor;
    file.close();
    //Loading score.
    QFile fileSave("data/scores/"+actor.getName()+".txt");
    fileSave.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
    QTextStream inScore(&fileSave);
    inScore << actor.getBestScore();
    //Loading total number of actions.
    QFile fileActNum("data/numberActions/"+actor.getName()+".txt");
    fileActNum.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
    QTextStream inActNum(&fileActNum);
    inActNum << actor.getTotalNumAction();
}

void Actor::loadActor(QString pathToSave, Actor &actor){
    QString fileName = pathToSave+actor.getName()+".txt";
    QFile file(fileName);
    file.open(file.ReadOnly);
    QTextStream in(&file);
    in >> actor;
    file.close();
    //Getting the best score
    QFile fileSave("data/scores/"+actor.getName()+".txt");
    fileSave.open(fileSave.ReadOnly);
    QTextStream inSave(&fileSave);
    QString scoreStr;
    inSave >> scoreStr;
    int score = scoreStr.toInt();
    actor.setBestScore(score);
    //Getting the total number of actions
    QFile fileActNum("data/numberActions/"+actor.getName()+".txt");
    fileActNum.open(fileActNum.ReadOnly);
    QTextStream inActNum(&fileActNum);
    QString actNum;
    inActNum >> actNum;
    int actNumInt = actNum.toInt();
    actor.totalNumAction = actNumInt;
}

Actor& Actor::loadActorFromFile(QString filePath){
    QFile file(filePath);
    QStringList fileNames = file.fileName().split("/");
    QString fileName = fileNames[fileNames.length()-1];
    QString fileDir = filePath.left(filePath.length()-fileName.length());
    file.open(file.ReadOnly);
    QTextStream in(&file);
    QString actorName;
    QString actorType;
    in >> actorName;
    in >> actorType;
    //building the actor
    NaiveActor* test = new NaiveActor();
    if (actorType.compare(QString(typeid(*test).name()))==0){
        NaiveActor* actor = new NaiveActor(fileName.left(fileName.length()-4));
        Actor::loadActor(fileDir, *actor);
        return *actor;
    }else{
        delete  test;
        Actor* test = new HumanActor();
        if(actorType.compare(QString(typeid(*test).name()))==0){
            HumanActor* actor = new HumanActor(fileName.left(fileName.length()-4));
            Actor::loadActor(fileDir, *actor);
            return *actor;
        }else{
            delete  test;
            Actor* test = new CpuActor();
            if(actorType.compare(QString(typeid(*test).name()))==0){
                CpuActor* actor = new CpuActor(fileName.left(fileName.length()-4));
                Actor::loadActor(fileDir, *actor);
                return *actor;
            }else{
                delete  test;
                Actor* test = new Actor();
                if(actorType.compare(QString(typeid(*test).name()))==0){
                    Actor* actor = new Actor(fileName);
                    Actor::loadActor(fileDir, *actor);
                    return *actor;
                }else{
                    qDebug() << filePath;
                    qDebug() << "Actor has not been recognized...";
                    throw QException{};
                }
            }
        }
    }
}

void Actor::stopGameSlot(){
    this->saveActor("data/actors/", *this);
}
