#ifndef KING_H
#define KING_H
#include "piece.h"

// Classic chess king. Protect him well.

class King : public Piece {
public:
    char toChar() override {
        return color == Color::White ? 'K' : 'k';
    }
    int getValue() override {
        return 0;
    }
    std::vector<PartialMove> getPossibleMoves() override {
        std::vector<PartialMove> moves;
        pushKingMoves(moves, MoveType::MoveOrAttack);
        return moves;
    }
};
#endif