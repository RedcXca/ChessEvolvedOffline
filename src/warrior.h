#ifndef WARRIOR_H
#define WARRIOR_H
#include "piece.h"

// Strong, resilient, simple. The Warrior can always be relied on to get the job done.

class Warrior : public Piece {
public:
    char toChar() override;
    int getValue() override;
    std::vector<PartialMove> getPossibleMoves() override;
};
#endif
