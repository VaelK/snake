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
public:
    Actor(QString name = "new_actor");
    Actor(QString name, std::unordered_map<QString, double> params);
    virtual void train(){};
    virtual int perform(){ return 0; };
    void saveActor();
    void loadActor();
    std::unordered_map<QString, double> getParams() const;
    void setParams(const std::unordered_map<QString, double> &value);
    QString getName() const;
    void setName(const QString &value);
    int getCurrentDirection() const;
    void setCurrentDirection(int value);

    virtual ~Actor();
};

QDataStream &operator<<(QDataStream &out, const Actor &actor);
QDataStream &operator>>(QDataStream &in, Actor &actor);

#endif // ACTOR_H
