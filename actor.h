#ifndef ACTOR_H
#define ACTOR_H
#include <unordered_map>
#include <istream>
#include <ostream>
#include "QString"
#include <QHash>

class Actor
{
private:
    std::unordered_map<QString, double> params;
    QString name;
    int currentDirection;
    QString pathToSave;
public:
    //Constructor
    Actor(QString name = "new_actor");
    Actor(QString name, std::unordered_map<QString, double> params);

    //Method
    //getter, setters
    std::unordered_map<QString, double> getParams() const;
    void setParams(const std::unordered_map<QString, double> &value);
    QString getName() const;
    void setName(const QString &value);
    int getCurrentDirection() const;
    void setCurrentDirection(int value);
    //Other methods
    virtual void train(){};
    virtual int perform(){ return 0; };
    void saveActor();
    void loadActor();
    QList<QString> listActor();

    //Destructor
    virtual ~Actor();
    QString getPathToSave() const;
    void setPathToSave(const QString &value);
};

QDataStream &operator<<(QDataStream &out, const Actor &actor);
QDataStream &operator>>(QDataStream &in, Actor &actor);

#endif // ACTOR_H
