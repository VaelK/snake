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

int Actor::getCurrentScore() const
{
    return currentScore;
}

Actor::Actor(QString name, QHash<QString, double> params)
{
    this->name = name;
    this->params = params;
    this->bestScore = 0;
    this->currentScore = 0;
}

Actor::~Actor(){}

void Actor::saveActor(QString pathToSave, Actor &actor){
    QString fileName = pathToSave+actor.getName()+".txt";
    QFile file(fileName);
    file.open(file.ReadWrite);
    QTextStream out(&file);
    out << actor;
    file.close();
    //Checking if a score file exists. If not creating one.
    QString fileSaveName = "data/scores/"+actor.getName()+".txt";
    QFile fileSave(fileName);
    fileSave.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
    QTextStream inScore(&fileSave);
    inScore << actor.getBestScore();
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
    QString scoreStr = 0;
    inSave >> scoreStr;
    int score = scoreStr.toInt();
    actor.setBestScore(score);
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
            Actor* test = new Actor();
            if(actorType.compare(QString(typeid(*test).name()))==0){
                Actor* actor = new Actor(fileName);
                Actor::loadActor(fileDir, *actor);
                return *actor;
            }else{
                throw QException{};
            }
        }
    }
}

