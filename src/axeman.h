#ifndef AXEMAN_H
#define AXEMAN_H
#include "Piece.h"

// Axeman is a more defensive, shorter ranged bishop that can swap color complexes

struct Axeman : Piece {
    char toChar() override;
    int getValue() override;
    std::vector<PartialMove> getPossibleMoves() override;
    using Piece::Piece;
};
#endif
