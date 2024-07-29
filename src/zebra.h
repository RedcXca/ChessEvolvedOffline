#ifndef ZEBRA_H
#define ZEBRA_H
#include "Piece.h"

// Zebra moves are immensely tricky to predict, but in the right hands their reach is devastating

struct Zebra : Piece {
    char toChar() override;
    int getValue() override;
    std::vector<PartialMove> getPossibleMoves() override;
    using Piece::Piece;
};
#endif
