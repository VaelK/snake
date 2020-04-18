#ifndef ACTOR_H
#define ACTOR_H
#include <unordered_map>
#include <istream>
#include <ostream>

class Actor
{
private:
    std::unordered_map<std::string, double> params;
    std::string name;
    int currentDirection;
public:
    Actor(std::string name = "new_actor");

    virtual void train(){};
    virtual int perform(){};
    virtual void saveActor(){};
    std::unordered_map<std::string, double> getParams() const;
    void setParams(const std::unordered_map<std::string, double> &value);
    std::string getName() const;
    void setName(const std::string &value);
    int getCurrentDirection() const;
    void setCurrentDirection(int value);
    std::string actor2str();
    void str2actor(std::string);

    virtual ~Actor();
};


#endif // ACTOR_H
