#ifndef ROOK_H
#define ROOK_H
#include "piece.h"

// Classic chess rook

class Rook : public Piece {
public:
    char toChar() override;
    int getValue() override;
    std::vector<PartialMove> getPossibleMoves() override;
};
#endif