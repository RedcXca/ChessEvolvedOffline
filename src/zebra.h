#ifndef ZEBRA_H
#define ZEBRA_H
#include "piece.h"

// Zebra moves are immensely tricky to predict, but in the right hands their reach is devastating

class Zebra : public Piece {
public:
    char toChar() override;
    int getValue() override;
    std::vector<PartialMove> getPossibleMoves() override;
};
#endif
