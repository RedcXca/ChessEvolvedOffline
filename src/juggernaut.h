#ifndef JUGGERNAUT_H
#define JUGGERNAUT_H
#include "piece.h"

// A dangerous piece with tons of power at close range. Watch your king next to this piece!

class Juggernaut : public Piece {
public:
    char toChar() override;
    int getValue() override;
    std::vector<PartialMove> getPossibleMoves() override;
};
#endif