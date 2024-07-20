#ifndef LEGIONARY_H
#define LEGIONARY_H
#include "piece.h"

// Legionary is very slow to move, but very deadly on defense

class Legionary : public Piece {
public:
    char toChar() override {
        return color == Color::White ? 'L' : 'l';
    }
    int getValue() override {
        return 5;
    }
    std::vector<PartialMove> getPossibleMoves() override {
        std::vector<PartialMove> moves;
        pushKingMoves(moves, MoveType::MoveOrAttack);
        pushBishopMoves(moves, 3, MoveType::AttackOnly, 2);
        pushRookMoves(moves, 2, MoveType::AttackOnly, 2);
        return moves;
    }
};
#endif