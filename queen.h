#ifndef QUEEN_H
#define QUEEN_H
#include "piece.h"

// Classic chess queen

class Queen : public Piece {
public:
    char toChar() override {
        return color == Color::White ? 'Q' : 'q';
    }
    int getValue() override {
        return 9;
    }
    std::vector<PartialMove> getPossibleMoves() override {
        std::vector<PartialMove> moves;
        pushBishopMoves(moves, 7, MoveType::MoveOrAttack);
        pushRookMoves(moves, 7, MoveType::MoveOrAttack);
        return moves;
    }
};
#endif