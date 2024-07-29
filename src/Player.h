#ifndef PLAYER_H
#define PLAYER_H
#include "MoveInput.h"
#include "Board.h"
struct Player {
    virtual MoveInput getNextMove(Board&) = 0;
};
#endif
