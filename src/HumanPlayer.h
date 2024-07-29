#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H
#include "Player.h"
struct HumanPlayer : Player {
    MoveInput getNextMove(Board&) override;
    using Player::Player;
};
#endif
