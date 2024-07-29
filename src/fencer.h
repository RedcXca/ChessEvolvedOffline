#ifndef FENCER_H
#define FENCER_H
#include "Piece.h"

// Fencer has the ability to teleport deep into enemy lines, posing dangerous threats

struct Fencer : Piece {
    char toChar() override;
    int getValue() override;
    std::vector<PartialMove> getPossibleMoves() override;
    using Piece::Piece;
};
#endif
