#ifndef PAWN_H
#define PAWN_H
#include "Piece.h"

// Classic chess pawn

struct Pawn : Piece {
    char toChar() override;
    int getValue() override;
    std::vector<PartialMove> getPossibleMoves() override;
    using Piece::Piece;
};
#endif
