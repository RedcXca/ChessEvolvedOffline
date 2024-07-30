#ifndef COMPUTERLEVEL3_H
#define COMPUTERLEVEL3_H
#include "ComputerPlayer.h"

// Prioritizes avoiding captures, captures, checks
struct ComputerLevel3 : ComputerPlayer {
    MoveInput getNextMove(Board&) override;
    using ComputerPlayer::ComputerPlayer;
};
#endif
