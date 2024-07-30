#ifndef COMPUTERLEVEL4_H
#define COMPUTERLEVEL4_H
#include "ComputerPlayer.h"

struct ComputerLevel4 : ComputerPlayer {
    MoveInput getNextMove(Board&) override;
    int moveScore (Board&, Move);
    const int CHECKWEIGHT = 1;
    using ComputerPlayer::ComputerPlayer;
};
#endif
