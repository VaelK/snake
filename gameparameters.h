#ifndef GAMEPARAMETERS_H
#define GAMEPARAMETERS_H
#include "actor.h"

class GameParameters
{
public:
    static GameParameters& Instance();

    //Getters Setters
    int getBoardWidth() const;

    int getBoardHeight() const;

    int getActionPerMinutes() const;

    Actor getCurrentActor() const;
    void setCurrentActor(const Actor &value);

private:
    // Singleton design
    GameParameters& operator= (const GameParameters&){}
    GameParameters (const GameParameters&){}

    static GameParameters m_instance;
    GameParameters();
    ~GameParameters();

    //member function
    int boardWidth;
    int boardHeight;
    int actionPerMinutes;
    Actor currentActor;
};

#endif // GAMEPARAMETERS_H
