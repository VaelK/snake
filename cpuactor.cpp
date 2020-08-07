#include "cpuactor.h"
#include <QString>
#include "actor.h"
#include "QVector"
#include "celltype.h"
#include "QException"
#include "QDebug"
#include "QString"
#include <QPair>
CpuActor::CpuActor(QString name)
    : Actor{name}
{
    this->setType(ActorType::ia);
}
CpuActor::~CpuActor(){}

void CpuActor::train(){

}

Direction CpuActor::perform(Direction currentDirection, QVector<QVector<int>> position, QVector<QVector<CellType>> boardState){
    //Default direction
    QPair<Direction, int> best = QPair<Direction, int>(Direction::up, 0);
    //First refining
    if (position[0][1]-1 >= 0){
        if (boardState[position[0][0]][position[0][1]-1] == CellType::empty)
            best = QPair<Direction, int>(Direction::up, 0);
    }
    if (position[0][0]-1 >= 0){
        if (boardState[position[0][0]-1][position[0][1]] == CellType::empty)
            best = QPair<Direction, int>(Direction::left, 0);
    }
    if(position[0][0]+1 < boardState.length()) {
        if (boardState[position[0][0]+1][position[0][1]] == CellType::empty)
            best = QPair<Direction, int>(Direction::right, 0);
    }
    if (position[0][1]+1 < boardState[0].length()){
        if (boardState[position[0][0]][position[0][1]+1] == CellType::empty)
            best = QPair<Direction, int>(Direction::down, 0);
    }
    QHash<Direction, int> bestDir;
    bestDir = this->RankDirection(position, boardState);
    QHashIterator<Direction, int> i(bestDir);
    if(bestDir[Direction::up] > best.second) {
        if (position[0][1]-1 >= 0){
            if ((boardState[position[0][0]][position[0][1]-1] == CellType::empty) || (boardState[position[0][0]][position[0][1]-1] == CellType::apple))
                best = QPair<Direction, int>(Direction::up, bestDir[Direction::up]);
        }
    }
    if(bestDir[Direction::left] > best.second) {
        if (position[0][0]-1 >= 0){
            if ((boardState[position[0][0]-1][position[0][1]] == CellType::empty) || (boardState[position[0][0]-1][position[0][1]] == CellType::apple))
                best = QPair<Direction, int>(Direction::left, bestDir[Direction::left]);
        }
    }
    if(bestDir[Direction::right] > best.second) {
        if (position[0][0]+1 < boardState.length()){
            if ((boardState[position[0][0]+1][position[0][1]] == CellType::empty) || (boardState[position[0][0]+1][position[0][1]] == CellType::apple))
                best = QPair<Direction, int>(Direction::right, bestDir[Direction::right]);
        }
    }
    if(bestDir[Direction::down] > best.second) {
        if (position[0][1]+1 < boardState[0].length()){
            if ((boardState[position[0][0]][position[0][1]+1] == CellType::empty) || (boardState[position[0][0]][position[0][1]+1] == CellType::apple))
                best = QPair<Direction, int>(Direction::down, bestDir[Direction::down]);
        }
    }
    return best.first;
}

void CpuActor::requireActorAction(Direction dir, QVector<QVector<int>> position, QVector<QVector<CellType>> boardState){
    this->actorActionResponse(this->perform(dir, position, boardState));
    this->setTotalNumAction(this->getTotalNumAction()+1);
}

QHash<Direction, int> CpuActor::RankDirection(QVector<QVector<int>> position, QVector<QVector<CellType>> boardState){
    QVector<int> applePos = QVector<int>(2);
    for (int x=0; x<boardState.length(); x++){
        for (int y=0; y<boardState[x].length(); y++){
            if (boardState[x][y] == CellType::apple){
                applePos[0] = x;
                applePos[1] = y;
            }
        }
    }
    QVector<int> bestDirection = QVector<int>(2);
    bestDirection[0] = applePos[0] - position[0][0];
    bestDirection[1] = applePos[1] - position[0][1];
    QHash<Direction, int> res;
    QVector<Direction> listDir = QVector<Direction>(4);
    listDir[0] = Direction::up;
    listDir[1] = Direction::down;
    listDir[2] = Direction::left;
    listDir[3] = Direction::right;
    for (int i=0; i<listDir.length(); i++){
        res[listDir[i]] = this->DotProductDir(bestDirection, listDir[i]);
    }
    return res;
}

int CpuActor::DotProductDir(QVector<int> dir_1, Direction dir_2){
    QVector<int> dir_1_vec = dir_1;
    QVector<int> dir_2_vec = QVector<int>(2);
    switch (dir_2) {
        case Direction::up:
            dir_2_vec[0] = 0;
            dir_2_vec[1] = -1;
            break;
        case Direction::down:
            dir_2_vec[0] = 0;
            dir_2_vec[1] = 1;
            break;
        case Direction::left:
            dir_2_vec[0] = -1;
            dir_2_vec[1] = 0;
            break;
        case Direction::right:
            dir_2_vec[0] = 1;
            dir_2_vec[1] = 0;
            break;
    }
    int dotProd = dir_1_vec[0]*dir_2_vec[0] + dir_1_vec[1]*dir_2_vec[1];
    return dotProd;
}


