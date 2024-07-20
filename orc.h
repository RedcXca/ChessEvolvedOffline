#ifndef ORC_H
#define ORC_H
#include "piece.h"

// Simple, effective moveset: a king is surprisingly powerful when it cannot be checked

class Orc : public Piece {
    public:
    char toChar() override {
        return color == Color::White ? 'O' : 'o';
    }
    int getValue() override {
        return 3;
    }
    std::vector<PartialMove> getPossibleMoves() override {
        std::vector<PartialMove> moves;
        pushKingMoves(moves, MoveType::MoveOrAttack);
        return moves;
    }
};
#endif