#ifndef KING_H
#define KING_H
#include "piece.h"

// Classic chess king. Protect him well.

struct King : Piece {
    char toChar() override;
    int getValue() override;
    std::vector<PartialMove> getPossibleMoves() override;
    using Piece::Piece;
};
#endif
