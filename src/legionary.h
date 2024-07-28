#ifndef LEGIONARY_H
#define LEGIONARY_H
#include "piece.h"

// Legionary is very slow to move, but very deadly on defense

class Legionary : public Piece {
public:
    char toChar() override;
    int getValue() override;
    std::vector<PartialMove> getPossibleMoves() override;
};
#endif
