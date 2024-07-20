#ifndef PAWN_H
#define PAWN_H
#include "piece.h"

// Classic chess pawn

class Pawn : public Piece {
public:
    char toChar() override {
        return color == Color::White ? 'P' : 'p';
    }
    int getValue() override {
        return 1;
    }
    std::vector<PartialMove> getPossibleMoves() override {
        std::vector<PartialMove> moves;
        int direction = color == Color::White ? 1 : -1;
        moves.push_back({0, direction, MoveType::MoveOnly});
        moves.push_back({0, 2 * direction, MoveType::MoveOnly});
        moves.push_back({1, direction, MoveType::AttackOnly});
        moves.push_back({-1, direction, MoveType::AttackOnly});
        return moves;
    }
};
#endif