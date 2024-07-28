#ifndef WYVERN_H
#define WYVERN_H
#include "piece.h"

// Wyvern is agile and eternally tricky with its teleports

class Wyvern : public Piece {
public:
    char toChar() override;
    int getValue() override;
    std::vector<PartialMove> getPossibleMoves() override;
};
#endif
