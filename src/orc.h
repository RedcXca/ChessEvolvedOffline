#ifndef ORC_H
#define ORC_H
#include "piece.h"

// Simple, effective moveset: a king is surprisingly powerful when it cannot be checked

struct Orc : Piece {
    char toChar() override;
    int getValue() override;
    std::vector<PartialMove> getPossibleMoves() override;
    using Piece::Piece;
};
#endif
