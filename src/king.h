#ifndef KING_H
#define KING_H
#include "piece.h"

// Classic chess king. Protect him well.

class King : public Piece {
public:
    char toChar() override;
    int getValue() override;
    std::vector<PartialMove> getPossibleMoves() override;
};
#endif
