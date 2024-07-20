#ifndef WARRIOR_H
#define WARRIOR_H
#include "piece.h"

// Strong, resilient, simple. The Warrior can always be relied on to get the job done.

class Warrior : public Piece {
public:
    char toChar() override {
        return color == Color::White ? 'W' : 'w';
    }
    int getValue() override {
        return 3;
    }
    std::vector<PartialMove> getPossibleMoves() override {
        std::vector<PartialMove> moves;
        pushRookMoves(moves, 2, MoveType::MoveOrAttack);
        pushBishopMoves(moves, 2, MoveType::MoveOrAttack);
        return moves;
    }
};
#endif