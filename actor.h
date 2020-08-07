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
#include <QObject>
#include <ActorType.h>

class Actor : public QObject
{
    Q_OBJECT

private:
    Q_DISABLE_COPY(Actor)
    QHash<QString, double> params;
    QString name;
    QString pathToSave;
    ActorType type;
    int bestScore;
    int totalNumAction;

public:
    //Constructor
    Actor(QString name = "new_actor", QHash<QString, double> params = QHash<QString, double>());

    //Method
    //getter, setters
    QHash<QString, double> getParams() const;
    void setParams(const QHash<QString, double> &value);
    QString getName() const;
    void setName(const QString &value);
    ActorType getType() const;
    void setType(const ActorType &value);
    void setBestScore(int value);
    int getBestScore() const;
    //Other methods
    virtual void train(){};
    virtual Direction perform(Direction, QVector<QVector<int>>, QVector<QVector<CellType>>){return Direction::up;};
    static void saveActor(QString path, Actor &actor);
    static Actor& loadActorFromFile(QString path);
    static void loadActor(QString path, Actor &actor);

    //Destructor
    virtual ~Actor();

    int getTotalNumAction() const;

    void setTotalNumAction(int value);

public slots:
    void stopGameSlot();

signals:
    void actorActionResponse(Direction dir);


};

#endif // ACTOR_H
