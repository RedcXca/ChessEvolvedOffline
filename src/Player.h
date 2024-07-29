#ifndef PLAYER_H
#define PLAYER_H
#include "MoveInput.h"
#include "board.h"
#include "color.h"
struct Player {
    virtual MoveInput getNextMove(const Board&, Color) = 0;
};
#endif
