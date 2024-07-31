#ifndef COMPUTERLEVEL5_H
#define COMPUTERLEVEL5_H
#include "ComputerPlayer.h"
struct ComputerLevel5 : ComputerPlayer {
    MoveInput getNextMove(Board&) override;
    using ComputerPlayer::ComputerPlayer;

private:
    int minimax(Board& board, int depth, bool maximize, int alpha, int beta);
};
#endif
