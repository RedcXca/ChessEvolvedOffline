#ifndef GHOST_H
#define GHOST_H
#include "piece.h"

// Color-bound and double-bound, the Ghost is tricky to maneuver but can deliver devasting forks

struct Ghost : Piece {
    char toChar() override;
    int getValue() override;
    std::vector<PartialMove> getPossibleMoves() override;
    using Piece::Piece;
};
#endif
