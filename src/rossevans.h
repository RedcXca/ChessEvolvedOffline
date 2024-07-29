#ifndef ROSS_EVANS_H
#define ROSS_EVANS_H
#include "piece.h"

// The man, the myth, the legend, the strongest piece in the game

class RossEvans : public Piece {
public:
    char toChar() override;
    int getValue() override;
    std::vector<PartialMove> getPossibleMoves() override;
    using Piece::Piece;
};
#endif
