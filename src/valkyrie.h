#ifndef VALKYRIE_H
#define VALKYRIE_H
#include "piece.h"

// Tricky to maneuver, devastating when maneuvered correctly

struct Valkyrie : Piece {
    char toChar() override;
    int getValue() override;
    std::vector<PartialMove> getPossibleMoves() override;
    using Piece::Piece;
};
#endif
