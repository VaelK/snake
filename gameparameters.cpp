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

void GameParameters::setActionPerMinutes(int value)
{
    actionPerMinutes = value;
}

int GameParameters::getBoardHeight() const
{
    return boardHeight;
}

void GameParameters::setBoardHeight(int value)
{
    boardHeight = value;
}

int GameParameters::getBoardWidth() const
{
    return boardWidth;
}

void GameParameters::setBoardWidth(int value)
{
    boardWidth = value;
}

GameParameters& GameParameters::Instance()
{
    return m_instance;
}
