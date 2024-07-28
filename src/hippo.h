#ifndef HIPPO_H
#define HIPPO_H
#include "piece.h"

// A very dangerous defensive piece, Hippo has very slow movement, unless provoked

class Hippo : public Piece {
public:
    char toChar() override;
    int getValue() override;
    std::vector<PartialMove> getPossibleMoves() override;
};
#endif
