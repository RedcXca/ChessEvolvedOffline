#ifndef PLAYER_H
#define PLAYER_H
#include "MoveInput.h"
#include "board.h"
#include "color.h"
class Player {
    Color color;

public:
    Player(Color color) : color(color) {}
    virtual MoveInput getNextMove(const Board&) = 0;
};
#endif
