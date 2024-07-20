#ifndef MOAT_H
#define MOAT_H
#include "piece.h"

// It will diligently protect exactly one row. It can move once, but never again

class Moat : public Piece {
public:
    char toChar() override {
        return color == Color::White ? 'M' : 'm';
    }
    int getValue() override {
        return 3;
    }
    std::vector<PartialMove> getPossibleMoves() override {
        std::vector<PartialMove> moves;
        for (int i = -7; i <= 7; i++) {
            moves.push_back({i, 0, MoveType::UnblockableAttackOnly});
        }
        if (!hasMoved) {
            moves.push_back({0, 1, MoveType::MoveOnly});
            moves.push_back({1, 1, MoveType::MoveOnly});
            moves.push_back({-1, 1, MoveType::MoveOnly});
        }
        return moves;
    }
};
#endif