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
#include <QDebug>

QTextStream& operator<<(QTextStream& out, const Actor& actor)
{
    //out << actor.getName();
    if (actor.getParams().count() > 0){
        for(QHash<QString, double>::iterator iter=actor.getParams().begin(); iter!=actor.getParams().end(); iter++){
            out << iter.key();
            out << QString::number(iter.value());
        }
    }
    return out;
}

QDataStream &operator>>(QDataStream& in, Actor& actor)
{
    QString name;
    QHash<QString, double> params;
    in >> name;
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

Actor::Actor(QString name)
{
    this->name = name;
    this->params = QHash<QString, double>();
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
    qDebug() << actor.getName();
    out << actor;
    qDebug() << "Wrting done";
    file.close();
}

void Actor::loadActor(QString pathToSave, Actor &actor){
    QString fileName = pathToSave+actor.getName()+".txt";
    QFile file(fileName);
    file.open(file.ReadOnly);
    QDataStream in(&file);
    in >> actor;
    qDebug() << "Reading done";
    file.close();
}
