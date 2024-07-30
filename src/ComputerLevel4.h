#ifndef COMPUTERLEVEL4_H
#define COMPUTERLEVEL4_H
#include "ComputerPlayer.h"

struct ComputerLevel4 : ComputerPlayer {
    MoveInput getNextMove(Board&) override;
    private:
    float moveScore (Board&, Move, bool log = false);
    int squareScore(Board&, Position);
    const float CHECKWEIGHT = 0.5;
    const float CENTRALIZATIONWEIGHT = 0.8;
    const float TOCENTRALIZATIONWEIGHT = 1.1;
    using ComputerPlayer::ComputerPlayer;
};
#endif
