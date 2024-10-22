#ifndef IMP_H
#define IMP_H

#include "Piece.h"

// Imp is dangerous on a single column of attack, but it can be a bit awkward to get on the right one

struct Imp : Piece {
    char toChar() override;
    int getValue() override;
    std::vector<PartialMove> getPossibleMoves() override;
    using Piece::Piece;
};
#endif
