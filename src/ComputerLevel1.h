#ifndef COMPUTERLEVEL1_H
#define COMPUTERLEVEL1_H
#include "ComputerPlayer.h"

// Totally random moves
struct ComputerLevel1 : ComputerPlayer {
    MoveInput getNextMove(Board&) override;
    using ComputerPlayer::ComputerPlayer;
};
#endif
