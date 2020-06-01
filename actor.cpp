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

Actor::Actor(QString name, QHash<QString, double> params)
{
    this->name = name;
    this->params = params;
}

Actor::~Actor(){}

void Actor::saveActor(QString pathToSave, Actor &actor){
    QString fileName = pathToSave+actor.getName()+".txt";
    QFile file(fileName);
    file.open(file.ReadWrite);
    QTextStream out(&file);
    out << actor;
    file.close();
}

void Actor::loadActor(QString pathToSave, Actor &actor){
    QString fileName = pathToSave+actor.getName()+".txt";
    QFile file(fileName);
    file.open(file.ReadOnly);
    QTextStream in(&file);
    in >> actor;
    file.close();
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
    NaiveActor* test = new NaiveActor();
    if (actorType.compare(QString(typeid(*test).name()))==0){
        NaiveActor* actor = new NaiveActor(fileName.left(fileName.length()-4));
        qDebug() << "New naive actor created";
        Actor::loadActor(fileDir, *actor);
        qDebug() << static_cast<int>(actor->getType());
        return *actor;
    }else{
        delete  test;
        Actor* test = new HumanActor();
        if(actorType.compare(QString(typeid(test).name()))==0){
            HumanActor* actor = new HumanActor(fileName.left(fileName.length()-4));
            Actor::loadActor(fileDir, *actor);
            return *actor;
        }else{
            delete  test;
            Actor* test = new Actor();
            if(actorType.compare(QString(typeid(test).name()))==0){
                Actor* actor = new Actor(fileName);
                Actor::loadActor(fileDir, *actor);
                return *actor;
            }else{
                throw QException{};
            }
        }
    }
}

