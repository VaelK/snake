#include <stdint.h>
#include <inttypes.h>
#ifndef DIRECTION_H
#define DIRECTION_H
#include <QHash>

enum class Direction
{
    //Absolute direction of the snake in the board reference.
    left, right, up, down
};

inline bool operator==(Direction &e1, Direction &e2)
{
    return static_cast<int>(e1) == static_cast<int>(e2);
}

inline unsigned int qHash(const Direction &key, unsigned int seed)
{
    return qHash(static_cast<int>(key), seed);
}

#endif // DIRECTION_H
