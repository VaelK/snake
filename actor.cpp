#include "actor.h"
#include <sstream>
#include <utility>
std::unordered_map<std::string, double> Actor::getParams() const
{
    return params;
}

void Actor::setParams(const std::unordered_map<std::string, double> &value)
{
    params = value;
}

std::string Actor::getName() const
{
    return name;
}

void Actor::setName(const std::string &value)
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

Actor::Actor(std::string name)
{
    this->name = name;
    this->currentDirection = 0;
}
Actor::~Actor(){}

std::string Actor::actor2str()
{
    std::string actorString = "";
    actorString += name;
    for(auto iter=this->params.begin(); iter!=this->params.end(); iter++){
        actorString += " ";
        actorString += iter->first;
        actorString += " ";
        actorString += iter->second;
    }
    return actorString;
}

void Actor::str2actor(std::string actorString)
{
    std::istringstream iss(actorString);
    iss >> name;
    this->setName(name);
    std::unordered_map<std::string, double> params = this->getParams();
    std::string key = "";
    double val = 0.0;
    while (!iss.eof()) {
        iss >> key;
        iss >> val;
        params.insert(std::make_pair(key, val));
    }
    this->setParams(params);
}

