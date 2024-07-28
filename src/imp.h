#ifndef IMP_H
#define IMP_H

#include "piece.h"

// Imp is dangerous on a single column of attack, but it can be a bit awkward to get on the right one

class Imp : public Piece {
public:
    char toChar() override;
    int getValue() override;
    std::vector<PartialMove> getPossibleMoves() override;
};
#endif