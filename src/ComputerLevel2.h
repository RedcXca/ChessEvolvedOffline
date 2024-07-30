#ifndef COMPUTERLEVEL2_H
#define COMPUTERLEVEL2_H
#include "ComputerPlayer.h"

// Prioritizes captures, checks
struct ComputerLevel2 : ComputerPlayer {
    MoveInput getNextMove(Board&) override;
    using ComputerPlayer::ComputerPlayer;
};
#endif
