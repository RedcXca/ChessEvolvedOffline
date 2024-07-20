#ifndef PARTIALMOVE_H
#define PARTIALMOVE_H
#include "movetype.h"
struct PartialMove {
    int deltaX, deltaY;
    MoveType type;
};
#endif