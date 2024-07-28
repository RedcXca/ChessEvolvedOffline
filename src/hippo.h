#ifndef HIPPO_H
#define HIPPO_H
#include "piece.h"

// A very dangerous defensive piece, Hippo has very slow movement, unless provoked

struct Hippo : Piece {
    char toChar() override;
    int getValue() override;
    std::vector<PartialMove> getPossibleMoves() override;
    using Piece::Piece;
};
#endif
