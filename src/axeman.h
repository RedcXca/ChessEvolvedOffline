#ifndef AXEMAN_H
#define AXEMAN_H
#include "piece.h"

// Axeman is a more defensive, shorter ranged bishop that can swap color complexes

class Axeman : public Piece {
public:
    char toChar() override;
    int getValue() override;
    std::vector<PartialMove> getPossibleMoves() override;
};
#endif