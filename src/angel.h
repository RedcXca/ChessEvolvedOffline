#ifndef ANGEL_H
#define ANGEL_H
#include "piece.h"

// Angel is a strong, mobile piece with high checkmating potential

class Angel : public Piece {
public:
    char toChar() override;
    int getValue() override;
    std::vector<PartialMove> getPossibleMoves() override;
};
#endif
