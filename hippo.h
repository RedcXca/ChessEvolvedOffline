#ifndef HIPPO_H
#define HIPPO_H
#include "piece.h"

// A very dangerous defensive piece, Hippo has very slow movement, unless provoked

class Hippo : public Piece {
public:
    char toChar() override {
        return color == Color::White ? 'H' : 'h';
    }
    int getValue() override {
        return 7;
    }
    std::vector<PartialMove> getPossibleMoves() override {
        std::vector<PartialMove> moves;
        pushKnightMoves(moves, MoveType::UnblockableAttackOnly);
        pushValkyrieMoves(moves, MoveType::UnblockableAttackOnly);
        pushRookMoves(moves, 1, MoveType::MoveOrAttack);
        pushBishopMoves(moves, 1, MoveType::AttackOnly);
        pushRookMoves(moves, 2, MoveType::UnblockableAttackOnly, 2);
        return moves;
    }
};
#endif