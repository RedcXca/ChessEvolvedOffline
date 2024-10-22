#ifndef ROOK_H
#define ROOK_H
#include "Piece.h"

// Classic chess rook

struct Rook : Piece {
    char toChar() override;
    int getValue() override;
    std::vector<PartialMove> getPossibleMoves() override;
    using Piece::Piece;
};
#endif
