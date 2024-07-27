#ifndef QUEEN_H
#define QUEEN_H
#include "piece.h"

// Classic chess queen

class Queen : public Piece {
public:
    char toChar() override;
    int getValue() override;
    std::vector<PartialMove> getPossibleMoves() override;
};
#endif