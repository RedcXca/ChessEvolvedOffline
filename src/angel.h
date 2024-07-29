#ifndef ANGEL_H
#define ANGEL_H
#include "Piece.h"

// Angel is a strong, mobile piece with high checkmating potential

struct Angel : Piece {
    char toChar() override;
    int getValue() override;
    std::vector<PartialMove> getPossibleMoves() override;
    using Piece::Piece;
};
#endif
