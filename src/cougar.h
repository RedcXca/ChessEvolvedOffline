#ifndef COUGAR_H
#define COUGAR_H
#include "piece.h"

// Unpredictable piece with few threat squares, but very tricky mobility and ability to infiltrate

class Cougar : public Piece {
public:
    char toChar() override;
    int getValue() override;
    std::vector<PartialMove> getPossibleMoves() override;
};
#endif
