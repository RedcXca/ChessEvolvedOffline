#include "ComputerPlayer.h"

// Prioritizes captures, checks
struct ComputerLevel2 : ComputerPlayer {
    MoveInput getNextMove(Board&) override;
    using ComputerPlayer::ComputerPlayer;
};
