#ifndef GHOST_H
#define GHOST_H
#include "piece.h"

// Color-bound and double-bound, the Ghost is tricky to maneuver but can deliver devasting forks

class Ghost : public Piece {
public:
    char toChar() override;
    int getValue() override;
    std::vector<PartialMove> getPossibleMoves() override;
};
#endif