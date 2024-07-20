#ifndef ROOK_H
#define ROOK_H
#include "piece.h"

// Classic chess rook

class Rook : public Piece {
public:
    char toChar() override {
        return color == Color::White ? 'R' : 'r';
    }
    int getValue() override {
        return 5;
    }
    std::vector<PartialMove> getPossibleMoves() override {
        std::vector<PartialMove> moves;
        pushRookMoves(moves, 7, MoveType::MoveOrAttack);
        return moves;
    }
};
#endif