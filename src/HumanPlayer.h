#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H
#include "Player.h"
struct HumanPlayer : Player {
    MoveInput getNextMove(const Board&, Color) override;
};
#endif
