#ifndef ACTOR_H
#define ACTOR_H
#include <unordered_map>
#include <istream>
#include <ostream>
#include "QString"
#include <QHash>
#include "QObject"
#include "QTextStream"
#include <direction.h>
#include <celltype.h>

class Actor
{
private:
    QHash<QString, double> params;
    QString name;
    QString pathToSave;
public:
    //Constructor
    Actor(QString name = "new_actor");
    Actor(QString name, QHash<QString, double> params);

    //Method
    //getter, setters
    QHash<QString, double> getParams() const;
    void setParams(const QHash<QString, double> &value);
    QString getName() const;
    void setName(const QString &value);
    //Other methods
    virtual void train(){};
    virtual Direction perform(Direction, QList<int>, QList<QList<CellType>>){return Direction::up;};
    static void saveActor(QString path, Actor &actor);
    static void loadActor(QString path, Actor &actor);

    //Destructor
    virtual ~Actor();
};

#endif // ACTOR_H
