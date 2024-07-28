#ifndef SHINOBI_H
#define SHINOBI_H
#include "piece.h"

// Shinobi is a very tricky piece that is easy to get checkmated by if you're not careful.

class Shinobi : public Piece {
public:
    char toChar() override;
    int getValue() override;
    std::vector<PartialMove> getPossibleMoves() override;
};

#endif
