#include "ComputerPlayer.h"

// Totally random moves
struct ComputerLevel1 : ComputerPlayer {
    MoveInput getNextMove(Board&) override;
    using ComputerPlayer::ComputerPlayer;
};
