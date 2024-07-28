#ifndef VALKYRIE_H
#define VALKYRIE_H
#include "piece.h"

// Tricky to maneuver, devastating when maneuvered correctly

class Valkyrie : public Piece {
public:
    char toChar() override;
    int getValue() override;
    std::vector<PartialMove> getPossibleMoves() override;
};
#endif
