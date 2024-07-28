#ifndef MOAT_H
#define MOAT_H
#include "piece.h"

// It will diligently protect exactly one row. It can move once, but never again

struct Moat : Piece {
    char toChar() override;
    int getValue() override;
    std::vector<PartialMove> getPossibleMoves() override;
    using Piece::Piece;
};
#endif
