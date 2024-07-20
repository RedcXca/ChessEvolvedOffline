#ifndef BISHOP_H
#define BISHOP_H
#include "piece.h"

// Classic chess bishop

class Bishop : public Piece {
public:
    char toChar() override {
        return color == Color::White ? 'B' : 'b';
    }
    int getValue() override {
        return 3;
    }
    std::vector<PartialMove> getPossibleMoves() override {
        std::vector<PartialMove> moves;
        pushBishopMoves(moves, 7, MoveType::MoveOrAttack);
        return moves;
    }
};
#endif