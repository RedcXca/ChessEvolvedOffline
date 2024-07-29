#ifndef DEMON_H
#define DEMON_H
#include "Piece.h"

// Demon trades off some of the higher range of a rook for knight teleports

struct Demon : Piece {
    char toChar() override;
    int getValue() override;
    std::vector<PartialMove> getPossibleMoves() override;
    using Piece::Piece;
};
#endif
