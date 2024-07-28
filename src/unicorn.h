#ifndef UNICORN_H
#define UNICORN_H
#include "piece.h"

// Which is better, bishop or knight? "Why not both?" answers Unicorn

class Unicorn : public Piece {
public:
    char toChar() override;
    int getValue() override;
    std::vector<PartialMove> getPossibleMoves() override;
};
#endif
