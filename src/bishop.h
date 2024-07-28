#ifndef BISHOP_H
#define BISHOP_H
#include "piece.h"

// Classic chess bishop

class Bishop : public Piece {
public:
    char toChar() override;
    int getValue() override;
    std::vector<PartialMove> getPossibleMoves() override;
};
#endif
