#ifndef JUGGERNAUT_H
#define JUGGERNAUT_H
#include "piece.h"

// A dangerous piece with tons of power at close range. Watch your king next to this piece!

class Juggernaut : public Piece {
public:
    char toChar() override {
        return color == Color::White ? 'J' : 'j';
    }
    int getValue() override {
        return 7;
    }
    std::vector<PartialMove> getPossibleMoves() override {
        std::vector<PartialMove> moves;
        pushKnightMoves(moves, MoveType::UnblockableMoveOrAttack);
        pushKingMoves(moves, MoveType::MoveOrAttack);
        pushRookMoves(moves, 2, MoveType::MoveOrAttack, 2);
        return moves;
    }
};
#endif