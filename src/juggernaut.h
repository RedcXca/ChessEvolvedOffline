#ifndef JUGGERNAUT_H
#define JUGGERNAUT_H
#include "piece.h"

// A dangerous piece with tons of power at close range. Watch your king next to this piece!

struct Juggernaut : Piece {
    char toChar() override;
    int getValue() override;
    std::vector<PartialMove> getPossibleMoves() override;
    using Piece::Piece;
};
#endif
