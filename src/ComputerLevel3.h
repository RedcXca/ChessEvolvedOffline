#include "ComputerPlayer.h"

// Prioritizes avoiding captures, captures, checks
struct ComputerLevel3 : ComputerPlayer {
    MoveInput getNextMove(Board&) override;
    using ComputerPlayer::ComputerPlayer;
};
