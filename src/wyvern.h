#ifndef WYVERN_H
#define WYVERN_H
#include "piece.h"

// Wyvern is agile and eternally tricky with its teleports

struct Wyvern : Piece {
    char toChar() override;
    int getValue() override;
    std::vector<PartialMove> getPossibleMoves() override;
    using Piece::Piece;
};
#endif
