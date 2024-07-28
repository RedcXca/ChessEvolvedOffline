#ifndef PAWN_H
#define PAWN_H
#include "piece.h"

// Classic chess pawn

class Pawn : public Piece {
public:
    char toChar() override;
    int getValue() override;
    std::vector<PartialMove> getPossibleMoves() override;
};
#endif
