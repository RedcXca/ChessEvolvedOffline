#ifndef FENCER_H
#define FENCER_H
#include "piece.h"

// Fencer has the ability to teleport deep into enemy lines, posing dangerous threats

class Fencer : public Piece {
public:
    char toChar() override;
    int getValue() override;
    std::vector<PartialMove> getPossibleMoves() override;
};
#endif