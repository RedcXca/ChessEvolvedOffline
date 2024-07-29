#ifndef SHINOBI_H
#define SHINOBI_H
#include "Piece.h"

// Shinobi is a very tricky piece that is easy to get checkmated by if you're not careful.

struct Shinobi : Piece {
    char toChar() override;
    int getValue() override;
    std::vector<PartialMove> getPossibleMoves() override;
    using Piece::Piece;
};

#endif
