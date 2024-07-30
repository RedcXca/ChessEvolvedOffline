#ifndef COMPUTERLEVEL4_H
#define COMPUTERLEVEL4_H
#include "ComputerPlayer.h"

struct ComputerLevel4 : ComputerPlayer {
    MoveInput getNextMove(Board&) override;
    float moveScore (Board&, Move, bool log = false);
    const float CHECKWEIGHT = 0.5;
    const float CENTRALIZATIONWEIGHT = 0.8;
    using ComputerPlayer::ComputerPlayer;
};
#endif
