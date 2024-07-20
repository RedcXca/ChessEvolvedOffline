#ifndef ANGEL_H
#define ANGEL_H
#include "piece.h"

// Angel is a strong, mobile piece with high checkmating potential

class Angel : public Piece {
public:
    char toChar() override {
        return color == Color::White ? 'A' : 'a';
    }
    int getValue() override {
        return 7;
    }
    std::vector<PartialMove> getPossibleMoves() override {
        std::vector<PartialMove> moves;
        pushValkyrieMoves(moves, MoveType::UnblockableMoveOrAttack);
        pushRookMoves(moves, 2, MoveType::MoveOrAttack);
        return moves;
    }
};
#endif