#ifndef DEMON_H
#define DEMON_H
#include "piece.h"

// Demon trades off some of the higher range of a rook for knight teleports

class Demon : public Piece {
public:
    char toChar() override;
    int getValue() override;
    std::vector<PartialMove> getPossibleMoves() override;
};
#endif