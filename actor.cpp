#include "actor.h"
#include <sstream>
#include <utility>
#include <fstream>
#include "QString"
#include <QTextStream>
#include <QDataStream>
#include <QHash>
#include <QFile>
#include <QDirIterator>


QDataStream &operator<<(QDataStream &out, const Actor &actor)
{
    out << actor.getName();
    for(auto iter=actor.getParams().begin(); iter!=actor.getParams().end(); iter++){
        out << iter->first;
        out << QString::number(iter->second);
    }
    return out;
}

QDataStream &operator>>(QDataStream &in, Actor &actor)
{
    QString name;
    std::unordered_map<QString, double> params;
    in >> name;
    while (!(in.atEnd())) {
        QString key;
        QString val;
        in >> key;
        in >> val;
        bool ok = false;
        params.insert(std::make_pair(key, val.toDouble(&ok)));
    }
    actor.setName(name);
    actor.setParams(params);
    return in;
}

std::unordered_map<QString, double> Actor::getParams() const
{
    return params;
}

void Actor::setParams(const std::unordered_map<QString, double> &value)
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

int Actor::getCurrentDirection() const
{
    return currentDirection;
}

void Actor::setCurrentDirection(int value)
{
    currentDirection = value;
}

QString Actor::getPathToSave() const
{
    return pathToSave;
}

void Actor::setPathToSave(const QString &value)
{
    pathToSave = value;
}

Actor::Actor(QString name)
{
    this->name = name;
    this->currentDirection = 0;
    this->pathToSave = "./data/actors/";
}
Actor::Actor(QString name, std::unordered_map<QString, double> params)
{
    this->name = name;
    this->currentDirection = 0;
    this->params = params;
    this->pathToSave = "./data/actors/";
}

Actor::~Actor(){}

void Actor::saveActor(){
    QString fileName = this->getPathToSave()+this->name+".txt";
    QFile file(fileName);
    QDataStream out(&file);
    out << this;
}

void Actor::loadActor(){
    QString fileName = this->getPathToSave()+this->name+".txt";
    QFile file(fileName);
    QDataStream in(&file);
    in >> *this;
}

QList<QString> Actor::listActor(){
    QList<QString> list;
    QDirIterator dirIt(this->getPathToSave());
    while (dirIt.hasNext()) {
        QString fileName = dirIt.next();
        list.append(fileName.left(fileName.length()-4));
    }
    return list;
}


