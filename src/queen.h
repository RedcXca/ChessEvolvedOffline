#ifndef QUEEN_H
#define QUEEN_H
#include "Piece.h"

// Classic chess queen

struct Queen : Piece {
    char toChar() override;
    int getValue() override;
    std::vector<PartialMove> getPossibleMoves() override;
    using Piece::Piece;
};
#endif
