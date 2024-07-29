#ifndef PLAYER_H
#define PLAYER_H
#include "MoveInput.h"
#include "board.h"
struct Player {
    virtual MoveInput getNextMove(Board&) = 0;
};
#endif
