#ifndef ORC_H
#define ORC_H
#include "piece.h"

// Simple, effective moveset: a king is surprisingly powerful when it cannot be checked

class Orc : public Piece {
public:
    char toChar() override;
    int getValue() override;
    std::vector<PartialMove> getPossibleMoves() override;
};
#endif
