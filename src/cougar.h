#ifndef COUGAR_H
#define COUGAR_H
#include "Piece.h"

// Unpredictable piece with few threat squares, but very tricky mobility and ability to infiltrate

struct Cougar : Piece {
    char toChar() override;
    int getValue() override;
    std::vector<PartialMove> getPossibleMoves() override;
    using Piece::Piece;
};
#endif
