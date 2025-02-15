#ifndef BISHOP_H
#define BISHOP_H
#include "Piece.h"

// Classic chess bishop

struct Bishop : Piece {
    char toChar() override;
    int getValue() override;
    std::vector<PartialMove> getPossibleMoves() override;
    using Piece::Piece;
};
#endif
