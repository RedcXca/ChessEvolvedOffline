#ifndef KNIGHT_H
#define KNIGHT_H
#include "piece.h"

// Classic chess knight

struct Knight : Piece {
    char toChar() override;
    int getValue() override;
    std::vector<PartialMove> getPossibleMoves() override;
    using Piece::Piece;
};
#endif