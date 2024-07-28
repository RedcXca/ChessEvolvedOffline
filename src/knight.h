#ifndef KNIGHT_H
#define KNIGHT_H
#include "piece.h"

// Classic chess knight

class Knight : public Piece {
public:
    char toChar() override;
    int getValue() override;
    std::vector<PartialMove> getPossibleMoves() override;
};
#endif
