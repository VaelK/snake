#include "gameparameters.h"

GameParameters GameParameters::m_instance=GameParameters();

GameParameters::GameParameters()
{ 
    this->boardWidth = 30;
    this->boardHeight = 30;
    this->actionPerMinutes = 120;
    this->currentActor = Actor();
}

GameParameters::~GameParameters()
{
}

//Getters Setters
Actor GameParameters::getCurrentActor() const
{
    return currentActor;
}

void GameParameters::setCurrentActor(const Actor &value)
{
    currentActor = value;
}

int GameParameters::getActionPerMinutes() const
{
    return actionPerMinutes;
}


int GameParameters::getBoardHeight() const
{
    return boardHeight;
}

int GameParameters::getBoardWidth() const
{
    return boardWidth;
}


GameParameters& GameParameters::Instance()
{
    return m_instance;
}
