#ifndef WARRIOR_H
#define WARRIOR_H
#include "piece.h"

// Strong, resilient, simple. The Warrior can always be relied on to get the job done.

struct Warrior : Piece {
    char toChar() override;
    int getValue() override;
    std::vector<PartialMove> getPossibleMoves() override;
    using Piece::Piece;
};
#endif
