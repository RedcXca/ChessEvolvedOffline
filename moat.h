#ifndef MOAT_H
#define MOAT_H
#include "piece.h"

// It will diligently protect exactly one row. It can move once, but never again

class Moat : public Piece {
public:
    char toChar() override;
    int getValue() override;
    std::vector<PartialMove> getPossibleMoves() override;
};
#endif