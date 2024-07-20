#ifndef UNICORN_H
#define UNICORN_H
#include "piece.h"

// Which is better, bishop or knight? "Why not both?" answers Unicorn

class Unicorn : public Piece {
public:
    char toChar() override {
        return color == Color::White ? 'U' : 'u';
    }
    int getValue() override {
        return 7;
    }
    std::vector<PartialMove> getPossibleMoves() override {
        std::vector<PartialMove> moves;
        pushKnightMoves(moves, MoveType::UnblockableMoveOrAttack);
        pushBishopMoves(moves, 7, MoveType::MoveOrAttack);
        return moves;
    }
};
#endif